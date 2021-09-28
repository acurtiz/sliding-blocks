#ifndef SLIDINGBLOCKS_INCLUDE_LEVEL_LOADER_JSON_FILE_LOADER_H_
#define SLIDINGBLOCKS_INCLUDE_LEVEL_LOADER_JSON_FILE_LOADER_H_

#include <string>
#include <SDL2/SDL.h>
#include "rapidjson/document.h"
#include "level_loader.h"

namespace sliding_blocks {

class JsonFileLoader : public LevelLoader {

 public:
  explicit JsonFileLoader(GameComponent &game_component);
  void Load(const std::string &file_name);

 private:
  rapidjson::Document document_;

  template<typename SurfaceClass>
  void LoadSurfacesIntoVector(std::vector<SurfaceClass *> &vector,
                              SDL_Color color,
                              const std::string &json_field);

  void LoadStartPointsIntoVector(std::vector<StartPoint *> &vector);
  void LoadEndPointsIntoVector(std::vector<EndPoint *> &vector);
  void LoadEnemiesIntoVector(std::vector<Enemy *> &vector);
  GameComponent &game_component_;

};

}

#endif //SLIDINGBLOCKS_INCLUDE_LEVEL_LOADER_JSON_FILE_LOADER_H_
