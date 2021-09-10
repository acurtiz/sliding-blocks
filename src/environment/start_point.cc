#include "environment/start_point.h"
#include "environment/surface.h"

namespace sliding_blocks {

StartPoint::StartPoint(int id, int top_left_x, int top_left_y, int width, int height, SDL_Renderer *renderer)
    : Surface(top_left_x, top_left_y, width, height, renderer, START_POINT),
      id_(id) {}

int StartPoint::GetId() {
  return id_;
}

}



