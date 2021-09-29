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

  LoadSurfacesIntoVector(walls_, "walls");
  LoadSurfacesIntoVector(slick_floors_, "slick_floors");
  LoadSurfacesIntoVector(walkable_floors_, "walkable_floors");
  LoadStartPointsIntoVector(start_points_);
  LoadEndPointsIntoVector(end_points_);
  LoadEnemiesIntoVector(enemies_);
  level_name_ = document_["name"].GetString();
  level_width_ = document_["width"].GetInt();
  level_height_ = document_["height"].GetInt();

  // Add walls implicitly to surround the level
  SDL_Color wall_color = ConvertHexString(document_["walls"]["color"].GetString());
  walls_.push_back(new Wall(-1, 0, 1, GetLevelHeight(), wall_color, game_component_));
  walls_.push_back(new Wall(GetLevelWidth(), 0, 1, GetLevelHeight(), wall_color, game_component_));
  walls_.push_back(new Wall(0, -1, GetLevelWidth(), 1, wall_color, game_component_));
  walls_.push_back(new Wall(0, GetLevelHeight(), GetLevelWidth(), 1, wall_color, game_component_));

  // By default, every part of map is walkable floor
  SDL_Color walkable_floor_color = ConvertHexString(document_["walkable_floors"]["color"].GetString());
  walkable_floors_.push_back(new WalkableFloor(0,
                                               0,
                                               GetLevelWidth(),
                                               GetLevelHeight(),
                                               walkable_floor_color,
                                               game_component_));

}
template<typename SurfaceClass>
void JsonFileLoader::LoadSurfacesIntoVector(std::vector<SurfaceClass *> &vector,
                                            const std::string &json_field) {

  SDL_Color color = ConvertHexString(document_[json_field.c_str()]["color"].GetString());

  for (auto &m: document_[json_field.c_str()].GetObject()["objects"].GetArray()) {
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

  SDL_Color color = ConvertHexString(document_["start_points"]["color"].GetString());

  for (auto &m: document_["start_points"].GetObject()["objects"].GetArray()) {

    vector.push_back(
        new StartPoint(
            m.GetObject().FindMember("id")->value.GetInt(),
            m.GetObject().FindMember("x")->value.GetInt(),
            m.GetObject().FindMember("y")->value.GetInt(),
            m.GetObject().FindMember("width")->value.GetInt(),
            m.GetObject().FindMember("height")->value.GetInt(),
            color,
            game_component_));
  }

}

void JsonFileLoader::LoadEndPointsIntoVector(std::vector<EndPoint *> &vector) {

  SDL_Color color = ConvertHexString(document_["end_points"]["color"].GetString());

  for (auto &m: document_["end_points"]["objects"].GetArray()) {

    bool has_next_stage = m.GetObject().FindMember("has_next_stage")->value.GetBool();

    vector.push_back(
        has_next_stage ?
        new EndPoint(
            m.GetObject().FindMember("id")->value.GetInt(),
            m.GetObject().FindMember("x")->value.GetInt(),
            m.GetObject().FindMember("y")->value.GetInt(),
            m.GetObject().FindMember("width")->value.GetInt(),
            m.GetObject().FindMember("height")->value.GetInt(),
            color,
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
            color,
            game_component_
        )
    );
  }

}

void JsonFileLoader::LoadEnemiesIntoVector(std::vector<Enemy *> &vector) {

  SDL_Color color = ConvertHexString(document_["enemies"]["color"].GetString());

  for (auto &m: document_["enemies"]["objects"].GetArray()) {

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
              color,
              game_component_));
    } else {
      throw std::runtime_error(boost::str(boost::format("Unrecognized enemy type: %1%\n") % type));
    }

  }
}

SDL_Color JsonFileLoader::ConvertHexString(std::string str) {

  if (str.substr(0, 2) != "0x") {
    throw std::runtime_error("Color must start with '0x'\n");
  }

  int r, g, b;
  std::stringstream stream;

  stream << std::hex << str.substr(2, 2);
  stream >> r;
  stream.clear();

  stream << std::hex << str.substr(4, 2);
  stream >> g;
  stream.clear();

  stream << std::hex << str.substr(6, 2);
  stream >> b;
  stream.clear();

  return {
      (Uint8) r,
      (Uint8) g,
      (Uint8) b,
      0xFF
  };

}

}
