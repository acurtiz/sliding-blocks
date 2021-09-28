#ifndef SLINDINGBLOCKS_INCLUDE_SCENE_SCENE_H_
#define SLINDINGBLOCKS_INCLUDE_SCENE_SCENE_H_

#include <SDL2/SDL.h>
#include "game/game_component.h"

namespace sliding_blocks {

class SceneExecutor;

class Scene : public GameComponent {

 public:
  explicit Scene(SceneExecutor &game, GameComponent &game_component);
  virtual ~Scene();
  virtual void RunSingleIterationEventHandler(SDL_Event &event) = 0;
  virtual void RunSingleIterationLoopBody() = 0;

 protected:
  SceneExecutor &scene_executor_;

 private:
  SDL_Color background_color_ = {0xFF, 0x7F, 0x50, 0xFF};

};

}
#endif //SLINDINGBLOCKS_INCLUDE_SCENE_SCENE_H_
