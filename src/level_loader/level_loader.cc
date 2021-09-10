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

void LevelLoader::FreeAll() {

  FreeSurfaces(walls_);
  FreeSurfaces(walkable_floors_);
  FreeSurfaces(slick_floors_);
  FreeSurfaces(start_points_);
  FreeSurfaces(end_points_);

}

template<typename PointerContainer>
void LevelLoader::FreeSurfaces(PointerContainer surfaces) {

  while (!surfaces.empty()) {
    Surface *surface = surfaces.back();
    delete surface;
    surfaces.pop_back();
  }

}

}