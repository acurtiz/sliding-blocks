#include <SDL2/SDL.h>
#include "text/text.h"
#include "shape/rectangle.h"
#include "button/button_event.h"

#ifndef SLIDINGBLOCKS_INCLUDE_BUTTON_RECTANGULAR_BUTTON_H_
#define SLIDINGBLOCKS_INCLUDE_BUTTON_RECTANGULAR_BUTTON_H_

namespace sliding_blocks {

class RectangularButton : public Rectangle {

 public:
  RectangularButton(int top_left_x,
                    int top_left_y,
                    int width,
                    int height,
                    Text *label,
                    SDL_Renderer *renderer);
  void SetTopLeftPosition(int top_left_x, int top_left_y) override;
  ButtonEvent HandleEvent(SDL_Event *event);
  void Render();

 private:
  SDL_Renderer *renderer_;
  Text *label_;
  const SDL_Color *current_color_;
  const SDL_Color color_default_ = {0x93, 0xE9, 0xBE, 0xFF};
  const SDL_Color color_mouse_down_ = {0xDA, 0x70, 0xD6, 0xFF};
  const SDL_Color color_mouse_motion_ = {0xBB, 0xCC, 0xD6, 0xFF};

};

}

#endif //SLIDINGBLOCKS_INCLUDE_BUTTON_RECTANGULAR_BUTTON_H_
