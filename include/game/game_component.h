#ifndef SLIDINGBLOCKS_INCLUDE_GAME_GAME_COMPONENT_H_
#define SLIDINGBLOCKS_INCLUDE_GAME_GAME_COMPONENT_H_

#include <SDL2/SDL.h>
#include "game/camera.h"

namespace sliding_blocks {

/**
 * GameComponent is meant to hold basic functionality that every game component will likely need access to
 */
class GameComponent {

 public:
  GameComponent(SDL_Renderer *renderer, SDL_Window *window, int screen_width, int screen_height, Camera *camera);
  SDL_Renderer *GetRenderer() const;
  int GetScreenWidth() const;
  int GetScreenHeight() const;
  SDL_Window *GetWindow() const;
  Camera *GetCamera() const;
 private:
  SDL_Renderer *renderer_;
  const int screen_width_;
  const int screen_height_;
  SDL_Window *window_;
  Camera *camera_;

};

}

#endif //SLIDINGBLOCKS_INCLUDE_GAME_GAME_COMPONENT_H_
