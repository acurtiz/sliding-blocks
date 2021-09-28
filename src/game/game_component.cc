#include "game/game_component.h"
#include <SDL2/SDL.h>

namespace sliding_blocks {

GameComponent::GameComponent(SDL_Renderer *renderer,
                             SDL_Window *window,
                             int screen_width,
                             int screen_height)
    : renderer_(renderer),
      window_(window),
      screen_width_(screen_width),
      screen_height_(screen_height) {}

SDL_Renderer *GameComponent::GetRenderer() const {
  return renderer_;
}

SDL_Window *GameComponent::GetWindow() const {
  return window_;
}

int GameComponent::GetScreenWidth() const {
  return screen_width_;
}

int GameComponent::GetScreenHeight() const {
  return screen_height_;
}

}

