#include <SDL2/SDL.h>
#include <boost/format.hpp>
#include "environment/surface.h"
#include "collider/rectangular_collider.h"

namespace sliding_blocks {

Surface::Surface(int top_left_x,
                 int top_left_y,
                 int width,
                 int height,
                 SDL_Renderer *renderer,
                 SurfaceType surface_type)
    : Rectangle(top_left_x, top_left_y, width, height),
      RectangularCollider((Rectangle &) *this),
      renderer_(renderer),
      surface_type_(surface_type) {}

SurfaceType Surface::GetType() {
  return surface_type_;
}

SDL_Color Surface::GetColor() {
  switch (surface_type_) {
    case SLICK_FLOOR:
      return {0, 0, 0xFF, 0xFF}; // blue
    case NORMAL_FLOOR:
      return {0xFF, 0xFF, 0, 0xFF}; // yellow
    case WALL:
      return {0x80, 0x80, 0x80, 0xFF}; // grey
    default:
      throw std::runtime_error(boost::str(boost::format("Invalid surface type: %1%\n") % surface_type_));
  }
}

void Surface::Render() {

  // Get previous color
  SDL_Color previous_color;
  SDL_GetRenderDrawColor(renderer_, &previous_color.r, &previous_color.g, &previous_color.b, &previous_color.a);

  // Draw the object
  SDL_Color color = GetColor();
  SDL_SetRenderDrawColor(renderer_, color.r, color.g, color.b, color.a);
  SDL_Rect rect = {GetTopLeftX(), GetTopLeftY(), GetWidth(), GetHeight()};
  SDL_RenderFillRect(renderer_, &rect);

  // Restore prior color
  SDL_SetRenderDrawColor(renderer_, previous_color.r, previous_color.g, previous_color.b, previous_color.a);

}

}