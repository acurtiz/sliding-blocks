#ifndef SLIDINGBLOCKS_INCLUDE_POP_UP_MENU_DEATH_MENU_H_
#define SLIDINGBLOCKS_INCLUDE_POP_UP_MENU_DEATH_MENU_H_

#include <functional>
#include <SDL2/SDL_ttf.h>
#include "pop_up_menu/pop_up_menu.h"
#include "button/rectangular_button.h"
#include "text/text.h"

namespace sliding_blocks {

class DeathMenu : public PopUpMenu {

 public:
  DeathMenu(GameComponent &game_component,
            std::function<void()> main_menu_callback,
            std::function<void()> retry_callback);
  ~DeathMenu();

 private:
  std::function<void()> main_menu_callback_;
  std::function<void()> retry_callback_;
  void RunSingleIterationEventHandlerMenuContents(SDL_Event &event) override;
  void RunSingleIterationLoopBodyMenuContents() override;
  Text *menu_title_;
  TTF_Font *font_;
  Text *label_main_menu_;
  RectangularButton *button_main_menu_;
  Text *label_retry_;
  RectangularButton *button_retry_;

};

}

#endif //SLIDINGBLOCKS_INCLUDE_POP_UP_MENU_DEATH_MENU_H_
