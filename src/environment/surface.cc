#include <SDL2/SDL.h>
#include "environment/surface.h"
#include "collider/rectangular_collider.h"

namespace sliding_blocks {

Surface::Surface(int top_left_x,
                 int top_left_y,
                 int width,
                 int height,
                 SDL_Color color,
                 GameComponent &game_component)
    : Rectangle(top_left_x, top_left_y, width, height),
      RectangularCollider((Rectangle &) *this),
      GameComponent(game_component),
      color_(color) {}

void Surface::Render() {

  // Get previous color
  SDL_Color previous_color;
  SDL_GetRenderDrawColor(GetRenderer(), &previous_color.r, &previous_color.g, &previous_color.b, &previous_color.a);

  // Draw the object
  SDL_SetRenderDrawColor(GetRenderer(), color_.r, color_.g, color_.b, color_.a);
  SDL_Rect rect = {
      GetTopLeftX() - GetCamera()->GetTopLeftX(),
      GetTopLeftY() - GetCamera()->GetTopLeftY(),
      GetWidth(),
      GetHeight()
  };
  SDL_RenderFillRect(GetRenderer(), &rect);

  // Restore prior color
  SDL_SetRenderDrawColor(GetRenderer(), previous_color.r, previous_color.g, previous_color.b, previous_color.a);

}

SDL_Color Surface::GetColor() const {
  return color_;
}

}