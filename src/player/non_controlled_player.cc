#include "player/non_controlled_player.h"

namespace sliding_blocks {

NonControlledPlayer::NonControlledPlayer(GameComponent &game_component,
                                         int width,
                                         int height,
                                         int top_left_x,
                                         int top_left_y)
    : Rectangle(top_left_x, top_left_y, width, height),
      RectangularCollider((Rectangle &) *this),
      GameComponent(game_component),
      top_left_x_(top_left_x),
      top_left_y_(top_left_y),
      color_({0xAA, 0xAA, 0xAA, 0xAA}) {
}

void NonControlledPlayer::SetTopLeftPosition(double x, double y) {
  Rectangle::SetTopLeftPosition((int) x, (int) y);
  top_left_x_ = x;
  top_left_y_ = y;
}

void NonControlledPlayer::Render() {

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

}

