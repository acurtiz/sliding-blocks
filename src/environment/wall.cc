#include <SDL2/SDL.h>
#include "environment/wall.h"

namespace sliding_blocks {

Wall::Wall(int top_left_x, int top_left_y, int width, int height, SDL_Color color, GameComponent &game_component)
    : Surface(top_left_x, top_left_y, width, height, color, game_component) {}

};

