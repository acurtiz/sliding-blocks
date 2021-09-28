#include <SDL2/SDL.h>
#include "pop_up_menu/pop_up_menu.h"
#include "game/game_component.h"

namespace sliding_blocks {

PopUpMenu::PopUpMenu(int top_left_x,
                     int top_left_y,
                     int width,
                     int height,
                     SDL_Color color,
                     GameComponent &game_component)
    : Rectangle(top_left_x, top_left_y, width, height),
      GameComponent(game_component),
      menu_is_opened_(false),
      color_(color) {}

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
  SDL_GetRenderDrawColor(GetRenderer(),
                         &previous_color.r,
                         &previous_color.g,
                         &previous_color.b,
                         &previous_color.a);

  // Draw the object
  SDL_SetRenderDrawColor(GetRenderer(), color_.r, color_.g, color_.b, color_.a);
  SDL_Rect rect = {GetTopLeftX(), GetTopLeftY(), GetWidth(), GetHeight()};
  SDL_RenderFillRect(GetRenderer(), &rect);

  // Restore prior color
  SDL_SetRenderDrawColor(GetRenderer(), previous_color.r, previous_color.g, previous_color.b, previous_color.a);

}

}
