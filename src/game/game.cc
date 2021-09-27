#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <boost/format.hpp>
#include "game/game.h"
#include "scene/game_scene.h"
#include "scene/title_scene.h"

namespace sliding_blocks {

Game::Game() :
    scene_current_(nullptr),
    scene_next_(nullptr),
    screen_width_(500),
    screen_height_(540),
    window_(nullptr),
    renderer_(nullptr),
    global_quit_(false) {

  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
    throw std::runtime_error(
        boost::str(boost::format("SDL could not initialize, error: %1%\n") % SDL_GetError())
    );
  }

  window_ = SDL_CreateWindow("Sliding Blocks",
                             SDL_WINDOWPOS_UNDEFINED,
                             SDL_WINDOWPOS_UNDEFINED,
                             screen_width_,
                             screen_height_,
                             SDL_WINDOW_SHOWN);

  if (window_ == nullptr) {
    throw std::runtime_error(
        boost::str(boost::format("Window could not be created, error: %1%\n") % SDL_GetError())
    );
  }

  renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);

  if (renderer_ == nullptr) {
    throw std::runtime_error(
        boost::str(boost::format("Renderer could not be created, error: %1%\n") % SDL_GetError())
    );
  }

  if (TTF_Init() == -1) {
    throw std::runtime_error(
        boost::str(boost::format("SDL_ttf could not be initialized, error: %1%\n") % TTF_GetError())
    );
  }

  LoadScenes();

}

Game::~Game() {

  UnloadScenes();
  SDL_DestroyWindow(window_);
  window_ = nullptr;
  SDL_Quit();

}

void Game::SwitchScene(std::type_index scene_type) {

  auto scene_to_switch_to = type_to_scene_map_.find(scene_type);
  if (scene_to_switch_to == type_to_scene_map_.end()) {
    throw std::runtime_error("Scene not found\n");
  }

  scene_next_ = scene_to_switch_to->second;

}

void Game::Run() {

  scene_current_ = type_to_scene_map_[typeid(TitleScene)];

  SDL_Event event;

  while (!global_quit_) {

    if (scene_next_ != nullptr) {
      scene_current_ = scene_next_;
      scene_next_ = nullptr;
    }

    while (SDL_PollEvent(&event)) {

      if (global_quit_) {
        return;
      }

      if (event.type == SDL_QUIT) {
        global_quit_ = true;
      }

      scene_current_->RunSingleIterationEventHandler(event);
    }

    if (global_quit_) {
      return;
    }

    scene_current_->RunSingleIterationLoopBody();

    SDL_Delay(15);
  }

}

void Game::LoadScenes() {

  auto *title_scene = new TitleScene(*this);
  auto *game_scene = new GameScene(*this);
  type_to_scene_map_[typeid(TitleScene)] = title_scene;
  type_to_scene_map_[typeid(GameScene)] = game_scene;

}

void Game::UnloadScenes() {

  for (auto &entry: type_to_scene_map_) {
    delete entry.second;
  }

}

void Game::Quit() {
  global_quit_ = true;
}

int Game::GetScreenHeight() const {
  return screen_height_;
}

int Game::GetScreenWidth() const {
  return screen_width_;
}

SDL_Renderer *Game::GetRenderer() const {
  return renderer_;
}

}