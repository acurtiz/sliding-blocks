#include <vector>
#include "environment/surface.h"
#include "environment/start_point.h"
#include "environment/end_point.h"

#ifndef SLIDINGBLOCKS_INCLUDE_LEVEL_LOADER_LEVEL_LOADER_H_
#define SLIDINGBLOCKS_INCLUDE_LEVEL_LOADER_LEVEL_LOADER_H_

namespace sliding_blocks {

class LevelLoader {

 public:
  explicit LevelLoader(SDL_Renderer *renderer);
  std::vector<Surface *> GetSlickFloors();
  std::vector<Surface *> GetWalkableFloors();
  std::vector<Surface *> GetWalls();
  std::vector<StartPoint *> GetStartPoints();
  std::vector<EndPoint *> GetEndPoints();
  int GetLevelWidth() const;
  int GetLevelHeight() const;
  std::string GetLevelName() const;
  void FreeAll();

 protected:
  SDL_Renderer *renderer_;
  std::vector<Surface *> slick_floors_;
  std::vector<Surface *> walkable_floors_;
  std::vector<Surface *> walls_;
  std::vector<EndPoint *> end_points_;
  std::vector<StartPoint *> start_points_;
  int level_width_;
  int level_height_;
  std::string level_name_;

 private:
  template<typename PointerContainer>
  void FreeSurfaces(PointerContainer &surfaces);

};

}

#endif //SLIDINGBLOCKS_INCLUDE_LEVEL_LOADER_LEVEL_LOADER_H_
