#include <SDL2/SDL.h>

#ifndef SLINDINGBLOCKS_INCLUDE_GAME_GAME_H_
#define SLINDINGBLOCKS_INCLUDE_GAME_GAME_H_

namespace sliding_blocks {

class Game {

 public:
  Game();
  ~Game();
  void Run();

 private:
  const int screen_width_ = 800;
  const int screen_height_ = 600;
  SDL_Window *window_ = nullptr;
  SDL_Renderer *renderer_ = nullptr;
  bool global_quit_ = false;

};

}
#endif //SLINDINGBLOCKS_INCLUDE_GAME_GAME_H_
