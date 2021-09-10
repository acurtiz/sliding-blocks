#include "collider/rectangular_collider.h"

namespace sliding_blocks {

RectangularCollider::RectangularCollider(Rectangle &rectangle) : rectangle_(rectangle) {}

bool RectangularCollider::IsCollision(RectangularCollider &other) {

  int this_top_y = rectangle_.GetTopLeftY();
  int this_bottom_y = rectangle_.GetTopLeftY() + rectangle_.GetHeight();
  int this_left_x = rectangle_.GetTopLeftX();
  int this_right_x = rectangle_.GetTopLeftX() + rectangle_.GetWidth();

  int other_top_y = other.rectangle_.GetTopLeftY();
  int other_bottom_y = other.rectangle_.GetTopLeftY() + other.rectangle_.GetHeight();
  int other_left_x = other.rectangle_.GetTopLeftX();
  int other_right_x = other.rectangle_.GetTopLeftX() + other.rectangle_.GetWidth();

  // This rectangle below the other
  if (this_top_y >= other_bottom_y) {
    return false;
  }

  // This rectangle above the other
  if (this_bottom_y <= other_top_y) {
    return false;
  }

  // This rectangle left of the other
  if (this_right_x <= other_left_x) {
    return false;
  }

  // This rectangle right of the other
  if (this_left_x >= other_right_x) {
    return false;
  }

  // None of those conditions are true - must be overlap
  return true;

}

}