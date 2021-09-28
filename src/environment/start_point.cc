#include "environment/start_point.h"
#include "environment/surface.h"

namespace sliding_blocks {

StartPoint::StartPoint(int id, int top_left_x, int top_left_y, int width, int height, GameComponent &game_component)
    : Surface(top_left_x, top_left_y, width, height, {0xFF, 0xFF, 0x00, 0xFF}, game_component),
      id_(id) {}

int StartPoint::GetId() {
  return id_;
}

}



