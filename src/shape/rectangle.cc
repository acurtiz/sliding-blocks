#include "shape/rectangle.h"

namespace sliding_blocks {

Rectangle::Rectangle(int top_left_x, int top_left_y, int width, int height) {
  top_left_x_ = top_left_x;
  top_left_y_ = top_left_y;
  width_ = width;
  height_ = height;
}

int Rectangle::GetTopLeftX() {
  return top_left_x_;
}

int Rectangle::GetTopLeftY() {
  return top_left_y_;
}

int Rectangle::GetWidth() {
  return width_;
}

int Rectangle::GetHeight() {
  return height_;
}

void Rectangle::SetTopLeftPosition(int x, int y) {
  top_left_x_ = x;
  top_left_y_ = y;
}

void Rectangle::SetWidth(int width) {
  width_ = width;
}

void Rectangle::SetHeight(int height) {
  height_ = height;
}

}

