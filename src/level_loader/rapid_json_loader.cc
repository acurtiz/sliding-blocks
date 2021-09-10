#include <fstream>
#include <sstream>
#include "level_loader/rapid_json_loader.h"
#include "environment/surface.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"

namespace sliding_blocks {

RapidJsonLoader::RapidJsonLoader(std::string file_name, SDL_Renderer *renderer)
    : LevelLoader(renderer) {

  std::ifstream level_stream(file_name);
  std::stringstream level_buffer;
  level_buffer << level_stream.rdbuf();
  std::string level_string = level_buffer.str();
  level_stream.close();

  rapidjson::Document document;
  document.Parse(level_string.c_str());

  for (auto &m : document["walls"].GetArray()) {

    LevelLoader::walls_.push_back(
        new Surface(
            m.GetObject().FindMember("x")->value.GetInt(),
            m.GetObject().FindMember("y")->value.GetInt(),
            m.GetObject().FindMember("width")->value.GetInt(),
            m.GetObject().FindMember("height")->value.GetInt(),
            renderer_,
            WALL));
  }

  for (auto &m : document["slick_floors"].GetArray()) {

    LevelLoader::slick_floors_.push_back(
        new Surface(
            m.GetObject().FindMember("x")->value.GetInt(),
            m.GetObject().FindMember("y")->value.GetInt(),
            m.GetObject().FindMember("width")->value.GetInt(),
            m.GetObject().FindMember("height")->value.GetInt(),
            renderer_,
            SLICK_FLOOR));

  }

  for (auto &m : document["walkable_floors"].GetArray()) {

    LevelLoader::walkable_floors_.push_back(
        new Surface(
            m.GetObject().FindMember("x")->value.GetInt(),
            m.GetObject().FindMember("y")->value.GetInt(),
            m.GetObject().FindMember("width")->value.GetInt(),
            m.GetObject().FindMember("height")->value.GetInt(),
            renderer_,
            NORMAL_FLOOR));

  }

}

}
