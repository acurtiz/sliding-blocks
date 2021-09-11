#include <SDL2/SDL.h>
#include "scene/scene.h"

namespace sliding_blocks {

Scene::Scene(SDL_Renderer *renderer, SDL_Window *window, bool &global_quit)
    : global_quit_(global_quit), renderer_(renderer), window_(window), local_quit_(false) {
}

Scene::~Scene() {
  renderer_ = nullptr;
  window_ = nullptr;
}

void Scene::RunSingleIterationEventHandler(SDL_Event &event) {

  if (event.type == SDL_QUIT) {
    QuitGlobal();
  }

}

void Scene::Run() {

  RunPreLoop();

  SDL_Event event;

  while (!global_quit_ && !local_quit_) {

    while (SDL_PollEvent(&event)) {

      if (global_quit_ || local_quit_) {
        return;
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

}