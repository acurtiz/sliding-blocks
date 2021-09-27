#ifndef SLIDINGBLOCKS_INCLUDE_POP_UP_MENU_DEATH_MENU_H_
#define SLIDINGBLOCKS_INCLUDE_POP_UP_MENU_DEATH_MENU_H_

#include <SDL2_ttf/SDL_ttf.h>
#include "pop_up_menu/pop_up_menu.h"
#include "button/rectangular_button.h"
#include "text/text.h"

namespace sliding_blocks {

class DeathMenu : public PopUpMenu {

 public:
  DeathMenu(SDL_Renderer *renderer, int top_left_x, int top_left_y, int width, int height, Game &game);
  ~DeathMenu();

 private:
  void RunSingleIterationEventHandlerMenuContents(SDL_Event &event) override;
  void RunSingleIterationLoopBodyMenuContents() override;
  SDL_Renderer *renderer_;
  Text *menu_title_;
  TTF_Font *font_;
  Text *label_main_menu_;
  RectangularButton *button_main_menu_;
  Text *label_retry_;
  RectangularButton *button_retry_;

};

}

#endif //SLIDINGBLOCKS_INCLUDE_POP_UP_MENU_DEATH_MENU_H_
