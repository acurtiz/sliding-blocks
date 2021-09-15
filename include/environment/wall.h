#include <SDL2/SDL.h>
#include "environment/surface.h"

#ifndef SLIDINGBLOCKS_INCLUDE_ENVIRONMENT_WALL_H_
#define SLIDINGBLOCKS_INCLUDE_ENVIRONMENT_WALL_H_

namespace sliding_blocks {

class Wall : public Surface {

 public:
  Wall(int top_left_x, int top_left_y, int width, int height, SDL_Color color, SDL_Renderer *renderer);

};

}

#endif //SLIDINGBLOCKS_INCLUDE_ENVIRONMENT_WALL_H_
