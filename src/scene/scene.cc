#include <SDL2/SDL.h>
#include "scene/scene.h"

namespace sliding_blocks {

Scene::Scene(SDL_Renderer *renderer, SDL_Window *window, bool &global_quit)
    : global_quit_(global_quit), renderer_(renderer), window_(window), local_quit_(false),
      screen_width_(-1),
      screen_height_(-1) {

  SDL_GetWindowSize(window, &screen_width_, &screen_height_);
  printf("Detected screen width [%d], height [%d]\n", screen_width_, screen_height_);

}

Scene::~Scene() {
  renderer_ = nullptr;
  window_ = nullptr;
}

void Scene::Run() {

  RunPreLoop();

  SDL_Event event;

  while (!global_quit_ && !local_quit_) {

    while (SDL_PollEvent(&event)) {

      if (global_quit_ || local_quit_) {
        return;
      }

      if (event.type == SDL_QUIT) {
        QuitGlobal();
      }

      RunSingleIterationEventHandler(event);
    }

    if (global_quit_ || local_quit_) {
      return;
    }

    RunSingleIterationLoopBody();

    SDL_Delay(15);
  }

  RunPostLoop();

}

void Scene::QuitLocal() {
  local_quit_ = true;
}

void Scene::QuitGlobal() {
  global_quit_ = true;
}

int Scene::GetScreenHeight() {
  return screen_height_;
}

int Scene::GetScreenWidth() {
  return screen_width_;
}

}