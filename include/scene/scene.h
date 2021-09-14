#include <SDL2/SDL.h>
#include "game/game.h"

#ifndef SLINDINGBLOCKS_INCLUDE_SCENE_SCENE_H_
#define SLINDINGBLOCKS_INCLUDE_SCENE_SCENE_H_

namespace sliding_blocks {

class Scene {

 public:
  Scene(SDL_Renderer *renderer, SDL_Window *window, bool &global_quit);
  ~Scene();
  void Run();

 protected:
  void QuitLocal();
  void QuitGlobal();
  int GetScreenHeight();
  int GetScreenWidth();
  SDL_Renderer *renderer_;
  SDL_Window *window_;
  bool &global_quit_;
  bool local_quit_;

 private:
  virtual void RunPreLoop() = 0;
  virtual void RunPostLoop() = 0;
  virtual void RunSingleIterationEventHandler(SDL_Event &event) = 0;
  virtual void RunSingleIterationLoopBody() = 0;
  int screen_height_;
  int screen_width_;

  SDL_Color background_color_ = {0xFF, 0x7F, 0x50, 0xFF};

};

}
#endif //SLINDINGBLOCKS_INCLUDE_SCENE_SCENE_H_
