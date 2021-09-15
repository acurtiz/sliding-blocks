#include <SDL2/SDL.h>
#include "environment/walkable_floor.h"

namespace sliding_blocks {

WalkableFloor::WalkableFloor(int top_left_x,
                             int top_left_y,
                             int width,
                             int height,
                             SDL_Color color,
                             SDL_Renderer *renderer)
    : Surface(top_left_x, top_left_y, width, height, color, renderer) {}

};

