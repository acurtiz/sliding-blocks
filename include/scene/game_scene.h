#include "scene/scene.h"

#ifndef SLIDINGBLOCKS_INCLUDE_SCENE_GAME_SCENE_H_
#define SLIDINGBLOCKS_INCLUDE_SCENE_GAME_SCENE_H_

namespace sliding_blocks {

class GameScene : public Scene {

 public:
  GameScene(SDL_Renderer *renderer, SDL_Window *window, bool &global_quit, int screen_height, int screen_width);
  void RunPreLoop() override;
  void RunPostLoop() override;
  void RunSingleIterationEventHandler(SDL_Event &event) override;
  void RunSingleIterationLoopBody() override;

 private:
  int screen_height_;
  int screen_width_;

};

}

#endif //SLIDINGBLOCKS_INCLUDE_SCENE_GAME_SCENE_H_
