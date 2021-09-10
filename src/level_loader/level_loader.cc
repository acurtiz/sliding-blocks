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

}