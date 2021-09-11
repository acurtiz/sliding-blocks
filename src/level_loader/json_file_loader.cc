#include <fstream>
#include <sstream>
#include <boost/format.hpp>
#include "level_loader/json_file_loader.h"
#include "environment/surface.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"

namespace sliding_blocks {

JsonFileLoader::JsonFileLoader(SDL_Renderer *renderer)
    : LevelLoader(renderer) {}

void JsonFileLoader::Load(const std::string &file_name) {

  std::ifstream level_stream(file_name);
  if ((level_stream.rdstate() & std::ifstream::failbit) != 0) {
    throw std::runtime_error(boost::str(boost::format("Could not open file: %1%\n") % file_name.c_str()));
  }
  std::stringstream level_buffer;
  level_buffer << level_stream.rdbuf();
  std::string level_string = level_buffer.str();
  level_stream.close();

  document_.Parse(level_string.c_str());

  LoadSurfacesIntoVector(walls_, WALL, "walls");
  LoadSurfacesIntoVector(slick_floors_, SLICK_FLOOR, "slick_floors");
  LoadSurfacesIntoVector(walkable_floors_, NORMAL_FLOOR, "walkable_floors");
  LoadStartPointsIntoVector(start_points_, "start_points");
  LoadEndPointsIntoVector(end_points_, "end_points");

}

template<typename SurfaceClass>
void JsonFileLoader::LoadSurfacesIntoVector(std::vector<SurfaceClass *> &vector,
                                            SurfaceType surface_type,
                                            const std::string &json_field) {

  for (auto &m : document_[json_field.c_str()].GetArray()) {

    vector.push_back(
        new SurfaceClass(
            m.GetObject().FindMember("x")->value.GetInt(),
            m.GetObject().FindMember("y")->value.GetInt(),
            m.GetObject().FindMember("width")->value.GetInt(),
            m.GetObject().FindMember("height")->value.GetInt(),
            renderer_,
            surface_type));
  }

}

void JsonFileLoader::LoadStartPointsIntoVector(std::vector<StartPoint *> &vector,
                                               const std::string &json_field) {

  for (auto &m : document_[json_field.c_str()].GetArray()) {

    vector.push_back(
        new StartPoint(
            m.GetObject().FindMember("id")->value.GetInt(),
            m.GetObject().FindMember("x")->value.GetInt(),
            m.GetObject().FindMember("y")->value.GetInt(),
            m.GetObject().FindMember("width")->value.GetInt(),
            m.GetObject().FindMember("height")->value.GetInt(),
            renderer_));
  }

}

void JsonFileLoader::LoadEndPointsIntoVector(std::vector<EndPoint *> &vector,
                                             const std::string &json_field) {

  for (auto &m : document_[json_field.c_str()].GetArray()) {

    bool has_next_stage = m.GetObject().FindMember("has_next_stage")->value.GetBool();

    vector.push_back(
        has_next_stage ?
        new EndPoint(
            m.GetObject().FindMember("id")->value.GetInt(),
            m.GetObject().FindMember("x")->value.GetInt(),
            m.GetObject().FindMember("y")->value.GetInt(),
            m.GetObject().FindMember("width")->value.GetInt(),
            m.GetObject().FindMember("height")->value.GetInt(),
            m.GetObject().FindMember("next_stage_file_path")->value.GetString(),
            m.GetObject().FindMember("next_stage_start_point_id")->value.GetInt(),
            renderer_
        ) :
        new EndPoint(
            m.GetObject().FindMember("id")->value.GetInt(),
            m.GetObject().FindMember("x")->value.GetInt(),
            m.GetObject().FindMember("y")->value.GetInt(),
            m.GetObject().FindMember("width")->value.GetInt(),
            m.GetObject().FindMember("height")->value.GetInt(),
            renderer_
        )
    );
  }

}

}
