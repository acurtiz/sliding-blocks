#include <SDL2/SDL.h>
#include "collider/rectangular_collider.h"

#ifndef SLIDINGBLOCKS_INCLUDE_ENVIRONMENT_SURFACE_H_
#define SLIDINGBLOCKS_INCLUDE_ENVIRONMENT_SURFACE_H_

namespace sliding_blocks {

class Surface : public Rectangle, public RectangularCollider {

 public:
  Surface(int top_left_x, int top_left_y, int width, int height, SDL_Color color, SDL_Renderer *renderer);
  void Render();

 private:
  SDL_Color color_;
  SDL_Renderer *renderer_;

};

}

#endif //SLIDINGBLOCKS_INCLUDE_ENVIRONMENT_SURFACE_H_
