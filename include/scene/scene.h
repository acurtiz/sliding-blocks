#ifndef SLINDINGBLOCKS_INCLUDE_SCENE_SCENE_H_
#define SLINDINGBLOCKS_INCLUDE_SCENE_SCENE_H_

#include <SDL2/SDL.h>

namespace sliding_blocks {

class Game;

class Scene {

 public:
  explicit Scene(Game &game);
  virtual ~Scene();
  virtual void RunSingleIterationEventHandler(SDL_Event &event) = 0;
  virtual void RunSingleIterationLoopBody() = 0;

 protected:
  Game &game_;

 private:
  SDL_Color background_color_ = {0xFF, 0x7F, 0x50, 0xFF};

};

}
#endif //SLINDINGBLOCKS_INCLUDE_SCENE_SCENE_H_
