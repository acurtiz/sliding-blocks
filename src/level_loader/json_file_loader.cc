#include <fstream>
#include <sstream>
#include <boost/format.hpp>
#include "level_loader/json_file_loader.h"
#include "environment/surface.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "enemy/straight_moving_enemy.h"

namespace sliding_blocks {

JsonFileLoader::JsonFileLoader(GameComponent &game_component)
    : LevelLoader(),
      game_component_(game_component) {}

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

  LoadSurfacesIntoVector(walls_, {0xFF, 0x00, 0x00, 0xFF}, "walls");
  LoadSurfacesIntoVector(slick_floors_, {0x00, 0xFF, 0x00, 0xFF}, "slick_floors");
  LoadSurfacesIntoVector(walkable_floors_, {0xFF, 0xFF, 0xFF, 0xFF}, "walkable_floors");
  LoadStartPointsIntoVector(start_points_);
  LoadEndPointsIntoVector(end_points_);
  LoadEnemiesIntoVector(enemies_);
  level_name_ = document_["name"].GetString();
  level_width_ = document_["width"].GetInt();
  level_height_ = document_["height"].GetInt();

}

template<typename SurfaceClass>
void JsonFileLoader::LoadSurfacesIntoVector(std::vector<SurfaceClass *> &vector,
                                            SDL_Color color,
                                            const std::string &json_field) {

  for (auto &m: document_[json_field.c_str()].GetArray()) {

    vector.push_back(
        new SurfaceClass(
            m.GetObject().FindMember("x")->value.GetInt(),
            m.GetObject().FindMember("y")->value.GetInt(),
            m.GetObject().FindMember("width")->value.GetInt(),
            m.GetObject().FindMember("height")->value.GetInt(),
            color,
            game_component_));
  }

}

void JsonFileLoader::LoadStartPointsIntoVector(std::vector<StartPoint *> &vector) {

  for (auto &m: document_["start_points"].GetArray()) {

    vector.push_back(
        new StartPoint(
            m.GetObject().FindMember("id")->value.GetInt(),
            m.GetObject().FindMember("x")->value.GetInt(),
            m.GetObject().FindMember("y")->value.GetInt(),
            m.GetObject().FindMember("width")->value.GetInt(),
            m.GetObject().FindMember("height")->value.GetInt(),
            game_component_));
  }

}

void JsonFileLoader::LoadEndPointsIntoVector(std::vector<EndPoint *> &vector) {

  for (auto &m: document_["end_points"].GetArray()) {

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
            game_component_
        ) :
        new EndPoint(
            m.GetObject().FindMember("id")->value.GetInt(),
            m.GetObject().FindMember("x")->value.GetInt(),
            m.GetObject().FindMember("y")->value.GetInt(),
            m.GetObject().FindMember("width")->value.GetInt(),
            m.GetObject().FindMember("height")->value.GetInt(),
            game_component_
        )
    );
  }

}

void JsonFileLoader::LoadEnemiesIntoVector(std::vector<Enemy *> &vector) {

  for (auto &m: document_["enemies"].GetArray()) {

    std::string type = m.GetObject().FindMember("type")->value.GetString();

    if (type == "straight_moving") {
      vector.push_back(
          new StraightMovingEnemy(
              m.GetObject().FindMember("x")->value.GetInt(),
              m.GetObject().FindMember("y")->value.GetInt(),
              m.GetObject().FindMember("width")->value.GetInt(),
              m.GetObject().FindMember("height")->value.GetInt(),
              m.GetObject().FindMember("velocity_x")->value.GetDouble(),
              m.GetObject().FindMember("velocity_y")->value.GetDouble(),
              {
                  (Uint8) m.GetObject().FindMember("color")->value.GetObj().FindMember("r")->value.GetInt(),
                  (Uint8) m.GetObject().FindMember("color")->value.GetObj().FindMember("g")->value.GetInt(),
                  (Uint8) m.GetObject().FindMember("color")->value.GetObj().FindMember("b")->value.GetInt(),
                  0xFF
              },
              game_component_));
    } else {
      throw std::runtime_error(boost::str(boost::format("Unrecognized enemy type: %1%\n") % type));
    }

  }
}

}
