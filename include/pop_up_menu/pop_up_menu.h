#ifndef SLIDINGBLOCKS_INCLUDE_POP_UP_MENU_POP_UP_MENU_H_
#define SLIDINGBLOCKS_INCLUDE_POP_UP_MENU_POP_UP_MENU_H_

#include <SDL2/SDL.h>
#include "shape/rectangle.h"
#include "game/game.h"

namespace sliding_blocks {

class PopUpMenu : public Rectangle, public GameComponent {

 public:
  PopUpMenu(int top_left_x, int top_left_y, int width, int height, SDL_Color color, GameComponent &game_component);
  void Open();
  void Close();
  bool IsOpened() const;
  void RunSingleIterationEventHandler(SDL_Event &event);
  void RunSingleIterationLoopBody();

 private:
  void Render();
  virtual void RunSingleIterationLoopBodyMenuContents() = 0;
  virtual void RunSingleIterationEventHandlerMenuContents(SDL_Event &event) = 0;
  bool menu_is_opened_;
  SDL_Color color_;

};

}

#endif //SLIDINGBLOCKS_INCLUDE_POP_UP_MENU_POP_UP_MENU_H_
