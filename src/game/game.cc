#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_net/SDL_net.h>
#include <boost/format.hpp>
#include "game/game.h"
#include "game/game_component.h"
#include "game/scene_executor.h"
#include "game/camera.h"

namespace sliding_blocks {

Game::Game() :
    screen_width_(500),
    screen_height_(500),
    window_(nullptr),
    renderer_(nullptr),
    global_quit_(false),
    game_component_(nullptr) {

  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
    throw std::runtime_error(
        boost::str(boost::format("SDL could not initialize, error: %1%\n") % SDL_GetError())
    );
  }

  if (SDLNet_Init() != 0) {
    throw std::runtime_error(
        boost::str(boost::format("SDLNet could not initialize, error: %1%\n") % SDLNet_GetError())
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

  camera_ = new Camera(screen_width_, screen_height_, 0, 0);
  game_component_ = new GameComponent(renderer_, window_, screen_width_, screen_height_, camera_);
  scene_executor_ = new SceneExecutor(*game_component_);

}

Game::~Game() {

  SDL_DestroyWindow(window_);
  window_ = nullptr;

  SDL_DestroyRenderer(renderer_);
  renderer_ = nullptr;

  delete game_component_;
  delete scene_executor_;

  SDLNet_Quit();
  SDL_Quit();

}

void Game::Run() {

  scene_executor_->Run();

}

}