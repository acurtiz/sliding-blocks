#ifndef SLIDINGBLOCKS_INCLUDE_GAME_GAME_COMPONENT_H_
#define SLIDINGBLOCKS_INCLUDE_GAME_GAME_COMPONENT_H_

#include <SDL2/SDL.h>

namespace sliding_blocks {

/**
 * GameComponent is meant to hold basic functionality that every game component will likely need access to
 */
class GameComponent {

 public:
  GameComponent(SDL_Renderer *renderer, SDL_Window *window, int screen_width, int screen_height);
  SDL_Renderer *GetRenderer() const;
  int GetScreenWidth() const;
  int GetScreenHeight() const;
  SDL_Window *GetWindow() const;

 private:
  SDL_Renderer *renderer_;
  const int screen_width_;
  const int screen_height_;
  SDL_Window *window_;

};

}

#endif //SLIDINGBLOCKS_INCLUDE_GAME_GAME_COMPONENT_H_
