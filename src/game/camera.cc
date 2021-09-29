#include "game/camera.h"

namespace sliding_blocks {

Camera::Camera(int width, int height, int top_left_x, int top_left_y)
    : Rectangle(top_left_x, top_left_y, width, height),
      boundary_top_y_(-1),
      boundary_right_x_(-1),
      boundary_bottom_y_(-1),
      boundary_left_x_(-1) {}

void Camera::SetBoundaries(int top, int right, int bottom, int left) {
  boundary_right_x_ = right;
  boundary_top_y_ = top;
  boundary_bottom_y_ = bottom;
  boundary_left_x_ = left;
}

void Camera::CenterOnObject(Rectangle &obj) {

  // Get center point of object
  int center_x = obj.GetTopLeftX() + obj.GetWidth() / 2;
  int center_y = obj.GetTopLeftY() + obj.GetHeight() / 2;

  // Calculate the edges of camera if perfectly centered
  int left = center_x - GetWidth() / 2;
  int right = center_x + GetWidth() / 2;
  int top = center_y - GetHeight() / 2;
  int bottom = center_y + GetHeight() / 2;

  // If any edge exceeds boundary, update it
  left = boundary_left_x_ != -1 && boundary_left_x_ > left ? boundary_left_x_ : left;
  top = boundary_top_y_ != -1 && boundary_top_y_ > top ? boundary_top_y_ : top;

  if (boundary_right_x_ != -1 && boundary_right_x_ < right) {
    left = boundary_right_x_ - GetWidth();
  }

  if (boundary_bottom_y_ != -1 && boundary_bottom_y_ < bottom) {
    // Shift up
    top = boundary_bottom_y_ - GetHeight();
  }

  // Set the position
  SetTopLeftPosition(left, top);

}

}