#include <SDL2/SDL.h>
#include "shape/rectangle.h"

namespace sliding_blocks {

Rectangle::Rectangle(int top_left_x, int top_left_y, int width, int height) {
  top_left_x_ = top_left_x;
  top_left_y_ = top_left_y;
  width_ = width;
  height_ = height;
}

int Rectangle::GetTopLeftX() const {
  return top_left_x_;
}

int Rectangle::GetTopLeftY() const {
  return top_left_y_;
}

int Rectangle::GetWidth() const {
  return width_;
}

int Rectangle::GetHeight() const {
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

bool Rectangle::IsMouseInside() const {

  int mouse_x, mouse_y = 0;
  SDL_GetMouseState(&mouse_x, &mouse_y);

  return (mouse_x >= GetTopLeftX())
      && (mouse_x <= GetTopLeftX() + GetWidth())
      && (mouse_y >= GetTopLeftY())
      && (mouse_y <= GetTopLeftY() + GetHeight());

}

}

