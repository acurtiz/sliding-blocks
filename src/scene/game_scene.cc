#include "scene/game_scene.h"

namespace sliding_blocks {

GameScene::GameScene(SDL_Renderer *renderer,
                     SDL_Window *window,
                     bool &global_quit,
                     int screen_height,
                     int screen_width)
    : Scene(renderer, window, global_quit),
      screen_height_(screen_width),
      screen_width_(screen_width) {}

void GameScene::RunPreLoop() {
}

void GameScene::RunPostLoop() {
}

void GameScene::RunSingleIterationEventHandler(SDL_Event &event) {
}

void GameScene::RunSingleIterationLoopBody() {
}

}
