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
  // We need to set the position during object construction - to avoid calling a virtual member from a constructor,
  // we introduce this redundant non-virtual method
  void SetTopLeftPositionButton(int top_left_x, int top_left_y);
  SDL_Renderer *renderer_;
  Text *label_;
  const SDL_Color *current_color_;

  const SDL_Color color_default_ = {0x38, 0x9E, 0xED, 0xFF}; // Blue
  const SDL_Color color_mouse_down_ = {0x3A, 0xF7, 0xAF, 0xFF}; // Greenish
  const SDL_Color color_mouse_motion_ = {0x3A, 0xD7, 0xF7, 0xFF}; // Lighter Blue

};

}

#endif //SLIDINGBLOCKS_INCLUDE_BUTTON_RECTANGULAR_BUTTON_H_
