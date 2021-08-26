#include "scene/game_scene.h"
#include "player/player.h"

namespace sliding_blocks {

GameScene::GameScene(SDL_Renderer *renderer,
                     SDL_Window *window,
                     bool &global_quit,
                     int screen_height,
                     int screen_width)
    : Scene(renderer, window, global_quit),
      screen_height_(screen_width),
      screen_width_(screen_width),
      player_(nullptr) {}

void GameScene::RunPreLoop() {
  player_ = new Player(renderer_, 30, 30, 10, 10);
}

void GameScene::RunPostLoop() {
  delete player_;
  player_ = nullptr;
}

void GameScene::RunSingleIterationEventHandler(SDL_Event &event) {

  Scene::RunSingleIterationEventHandler(event);
  player_->HandleEvent(event);

}

void GameScene::RunSingleIterationLoopBody() {

  SDL_SetRenderDrawColor(renderer_, background_color_.r, background_color_.g, background_color_.b, background_color_.a);
  SDL_RenderClear(renderer_);

  player_->ProcessFrame();
  player_->Render();
}

}
