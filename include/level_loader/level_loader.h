#include <vector>
#include "environment/surface.h"
#include "environment/start_point.h"
#include "environment/end_point.h"
#include "environment/slick_floor.h"
#include "environment/walkable_floor.h"
#include "environment/wall.h"
#include "enemy/enemy.h"

#ifndef SLIDINGBLOCKS_INCLUDE_LEVEL_LOADER_LEVEL_LOADER_H_
#define SLIDINGBLOCKS_INCLUDE_LEVEL_LOADER_LEVEL_LOADER_H_

namespace sliding_blocks {

class LevelLoader {

 public:
  explicit LevelLoader(SDL_Renderer *renderer);
  std::vector<SlickFloor *> GetSlickFloors();
  std::vector<WalkableFloor *> GetWalkableFloors();
  std::vector<Wall *> GetWalls();
  std::vector<StartPoint *> GetStartPoints();
  std::vector<EndPoint *> GetEndPoints();
  std::vector<Enemy *> GetEnemies();
  int GetLevelWidth() const;
  int GetLevelHeight() const;
  std::string GetLevelName() const;
  void FreeAll();

 protected:
  SDL_Renderer *renderer_;
  std::vector<SlickFloor *> slick_floors_;
  std::vector<WalkableFloor *> walkable_floors_;
  std::vector<Wall *> walls_;
  std::vector<EndPoint *> end_points_;
  std::vector<StartPoint *> start_points_;
  std::vector<Enemy *> enemies_;
  int level_width_;
  int level_height_;
  std::string level_name_;

 private:
  template<typename PointerContainer>
  void FreePointersInContainer(PointerContainer &pointers);

};

}

#endif //SLIDINGBLOCKS_INCLUDE_LEVEL_LOADER_LEVEL_LOADER_H_
