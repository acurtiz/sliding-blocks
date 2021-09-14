#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <string>
#include "shape/rectangle.h"

#ifndef SLIDINGBLOCKS_INCLUDE_TEXT_TEXT_H_
#define SLIDINGBLOCKS_INCLUDE_TEXT_TEXT_H_

namespace sliding_blocks {

class Text {
 public:
  Text(SDL_Renderer *renderer, TTF_Font *font, SDL_Color color, std::string text, int wrap_length_pixels = -1);
  ~Text();
  void Free();
  void SetTopLeftPosition(int top_left_x, int top_left_y);
  int GetTopLeftX() const;
  int GetTopLeftY() const;
  int GetWidth() const;
  int GetHeight() const;
  void Render();
  std::string GetString() const;
 private:
  int top_left_x_;
  int top_left_y_;
  int width_;
  int height_;
  std::string text_string_;
  SDL_Texture *texture_;
  SDL_Renderer *renderer_;
};

}
#endif //SLIDINGBLOCKS_INCLUDE_TEXT_TEXT_H_
