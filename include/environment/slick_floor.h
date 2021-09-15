#include <SDL2/SDL.h>
#include "environment/surface.h"

#ifndef SLIDINGBLOCKS_INCLUDE_ENVIRONMENT_SLICK_FLOOR_H_
#define SLIDINGBLOCKS_INCLUDE_ENVIRONMENT_SLICK_FLOOR_H_

namespace sliding_blocks {

class SlickFloor : public Surface {

 public:
  SlickFloor(int top_left_x, int top_left_y, int width, int height, SDL_Color color, SDL_Renderer *renderer);

};

}

#endif //SLIDINGBLOCKS_INCLUDE_ENVIRONMENT_SLICK_FLOOR_H_
