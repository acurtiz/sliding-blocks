#include <SDL2/SDL.h>
#include "collider/rectangular_collider.h"

#ifndef SLIDINGBLOCKS_INCLUDE_ENVIRONMENT_SURFACE_H_
#define SLIDINGBLOCKS_INCLUDE_ENVIRONMENT_SURFACE_H_

namespace sliding_blocks {

enum SurfaceType {
  WALL,
  SLICK_FLOOR,
  NORMAL_FLOOR
};

class Surface : public Rectangle, public RectangularCollider {

 public:
  Surface(int top_left_x, int top_left_y, int width, int height, SDL_Renderer *renderer, SurfaceType surface_type);
  SurfaceType GetType();
  void Render();

 private:
  SDL_Color GetColor();
  SDL_Renderer *renderer_;
  SurfaceType surface_type_;

};

}

#endif //SLIDINGBLOCKS_INCLUDE_ENVIRONMENT_SURFACE_H_
