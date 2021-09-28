#ifndef SLINDINGBLOCKS_INCLUDE_GAME_GAME_H_
#define SLINDINGBLOCKS_INCLUDE_GAME_GAME_H_

#include <typeindex>
#include <map>
#include <SDL2/SDL.h>
#include "scene/scene.h"
#include "game/game_component.h"
#include "game/scene_executor.h"

namespace sliding_blocks {

class Game {

 public:
  Game();
  ~Game();
  void Run();

 private:
  GameComponent *game_component_;
  SceneExecutor *scene_executor_;
  const int screen_width_;
  const int screen_height_;
  SDL_Window *window_;
  SDL_Renderer *renderer_;
  bool global_quit_;

};

}
#endif //SLINDINGBLOCKS_INCLUDE_GAME_GAME_H_
