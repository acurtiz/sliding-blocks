#include "environment/end_point.h"
#include "environment/surface.h"

namespace sliding_blocks {

EndPoint::EndPoint(int id, int top_left_x, int top_left_y, int width, int height, SDL_Renderer *renderer)
    : Surface(top_left_x, top_left_y, width, height, renderer, END_POINT),
      id_(id) {}

int EndPoint::GetId() {
  return id_;
}

}
