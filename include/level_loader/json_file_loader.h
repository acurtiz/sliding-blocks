#include <string>
#include <SDL2/SDL.h>
#include "rapidjson/document.h"
#include "level_loader.h"

#ifndef SLIDINGBLOCKS_INCLUDE_LEVEL_LOADER_JSON_FILE_LOADER_H_
#define SLIDINGBLOCKS_INCLUDE_LEVEL_LOADER_JSON_FILE_LOADER_H_

namespace sliding_blocks {

class JsonFileLoader : public LevelLoader {

 public:
  explicit JsonFileLoader(SDL_Renderer *renderer);
  void Load(const std::string &file_name);

 private:
  rapidjson::Document document_;

  template<typename SurfaceClass>
  void LoadSurfacesIntoVector(std::vector<SurfaceClass *> &vector,
                              SurfaceType surface_type,
                              const std::string &json_field);

  void LoadStartPointsIntoVector(std::vector<StartPoint *> &vector);
  void LoadEndPointsIntoVector(std::vector<EndPoint *> &vector);
  void LoadEnemiesIntoVector(std::vector<Enemy *> &vector);

};

}

#endif //SLIDINGBLOCKS_INCLUDE_LEVEL_LOADER_JSON_FILE_LOADER_H_
