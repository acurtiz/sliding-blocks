#include <SDL2/SDL.h>
#include "environment/slick_floor.h"

namespace sliding_blocks {

SlickFloor::SlickFloor(int top_left_x,
                       int top_left_y,
                       int width,
                       int height,
                       SDL_Color color,
                       GameComponent &game_component)
    : Surface(top_left_x, top_left_y, width, height, color, game_component) {}

};

