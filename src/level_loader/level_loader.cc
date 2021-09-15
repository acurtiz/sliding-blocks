#include "level_loader/level_loader.h"

namespace sliding_blocks {

LevelLoader::LevelLoader(SDL_Renderer *renderer) {
  renderer_ = renderer;
}

std::vector<Surface *> LevelLoader::GetWalls() {
  return walls_;
}

std::vector<Surface *> LevelLoader::GetSlickFloors() {
  return slick_floors_;
}

std::vector<Surface *> LevelLoader::GetWalkableFloors() {
  return walkable_floors_;
}

std::vector<StartPoint *> LevelLoader::GetStartPoints() {
  return start_points_;
}

std::vector<EndPoint *> LevelLoader::GetEndPoints() {
  return end_points_;
}

std::vector<Enemy *> LevelLoader::GetEnemies() {
  return enemies_;
}

void LevelLoader::FreeAll() {

  FreePointersInContainer(walls_);
  FreePointersInContainer(walkable_floors_);
  FreePointersInContainer(slick_floors_);
  FreePointersInContainer(start_points_);
  FreePointersInContainer(end_points_);
  FreePointersInContainer(enemies_);

}

template<typename PointerContainer>
void LevelLoader::FreePointersInContainer(PointerContainer &pointers) {

  for (auto &pointer : pointers) {
    delete pointer;
  }

  pointers.clear();

}

int LevelLoader::GetLevelWidth() const {
  return level_width_;
}

int LevelLoader::GetLevelHeight() const {
  return level_height_;
}

std::string LevelLoader::GetLevelName() const {
  return level_name_;
}

}