#include <SDL2/SDL.h>
#include "environment/surface.h"
#include "collider/rectangular_collider.h"

namespace sliding_blocks {

Surface::Surface(int top_left_x,
                 int top_left_y,
                 int width,
                 int height,
                 SDL_Color color,
                 SDL_Renderer *renderer)
    : Rectangle(top_left_x, top_left_y, width, height),
      RectangularCollider((Rectangle &) *this),
      renderer_(renderer),
      color_(color) {}

void Surface::Render() {

  // Get previous color
  SDL_Color previous_color;
  SDL_GetRenderDrawColor(renderer_, &previous_color.r, &previous_color.g, &previous_color.b, &previous_color.a);

  // Draw the object
  SDL_SetRenderDrawColor(renderer_, color_.r, color_.g, color_.b, color_.a);
  SDL_Rect rect = {GetTopLeftX(), GetTopLeftY(), GetWidth(), GetHeight()};
  SDL_RenderFillRect(renderer_, &rect);

  // Restore prior color
  SDL_SetRenderDrawColor(renderer_, previous_color.r, previous_color.g, previous_color.b, previous_color.a);

}

}