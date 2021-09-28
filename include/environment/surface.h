#ifndef SLIDINGBLOCKS_INCLUDE_ENVIRONMENT_SURFACE_H_
#define SLIDINGBLOCKS_INCLUDE_ENVIRONMENT_SURFACE_H_

#include <SDL2/SDL.h>
#include "collider/rectangular_collider.h"
#include "game/game_component.h"

namespace sliding_blocks {

class Surface : public Rectangle, public RectangularCollider, public GameComponent {

 public:
  Surface(int top_left_x, int top_left_y, int width, int height, SDL_Color color, GameComponent &game_component);
  void Render();

 private:
  SDL_Color color_;

};

}

#endif //SLIDINGBLOCKS_INCLUDE_ENVIRONMENT_SURFACE_H_
