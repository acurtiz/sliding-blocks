#include <SDL2/SDL.h>
#include "pop_up_menu/pop_up_menu.h"
#include "game/game.h"

namespace sliding_blocks {

PopUpMenu::PopUpMenu(SDL_Renderer *renderer,
                     int top_left_x,
                     int top_left_y,
                     int width,
                     int height,
                     SDL_Color color,
                     Game &game)
    : Rectangle(top_left_x, top_left_y, width, height),
      game_(game),
      menu_is_opened_(false),
      color_(color),
      renderer_(renderer) {}

void PopUpMenu::Open() {
  menu_is_opened_ = true;
}

void PopUpMenu::Close() {
  menu_is_opened_ = false;
}

bool PopUpMenu::IsOpened() const {
  return menu_is_opened_;
}

void PopUpMenu::RunSingleIterationLoopBody() {

  if (IsOpened()) {
    Render();
    RunSingleIterationLoopBodyMenuContents();
  }

}

void PopUpMenu::RunSingleIterationEventHandler(SDL_Event &event) {

  if (IsOpened()) {
    RunSingleIterationEventHandlerMenuContents(event);
  }

}

void PopUpMenu::Render() {

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
