#include <vector>
#include "environment/surface.h"

#ifndef SLIDINGBLOCKS_INCLUDE_LEVEL_LOADER_LEVEL_LOADER_H_
#define SLIDINGBLOCKS_INCLUDE_LEVEL_LOADER_LEVEL_LOADER_H_

namespace sliding_blocks {

class LevelLoader {

 public:
  explicit LevelLoader(SDL_Renderer *renderer);
  virtual std::vector<Surface *> GetSlickFloors();
  virtual std::vector<Surface *> GetWalkableFloors();
  virtual std::vector<Surface *> GetWalls();

 protected:
  SDL_Renderer *renderer_;
  std::vector<Surface *> slick_floors_;
  std::vector<Surface *> walkable_floors_;
  std::vector<Surface *> walls_;

};

}

#endif //SLIDINGBLOCKS_INCLUDE_LEVEL_LOADER_LEVEL_LOADER_H_
