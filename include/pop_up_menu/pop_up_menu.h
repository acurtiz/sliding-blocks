#ifndef SLIDINGBLOCKS_INCLUDE_POP_UP_MENU_POP_UP_MENU_H_
#define SLIDINGBLOCKS_INCLUDE_POP_UP_MENU_POP_UP_MENU_H_

#include <SDL2/SDL.h>
#include "shape/rectangle.h"

namespace sliding_blocks {

class PopUpMenu : public Rectangle {

 public:
  PopUpMenu(SDL_Renderer *renderer, int top_left_x, int top_left_y, int width, int height, SDL_Color color);
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
  SDL_Renderer *renderer_;

};

}

#endif //SLIDINGBLOCKS_INCLUDE_POP_UP_MENU_POP_UP_MENU_H_
