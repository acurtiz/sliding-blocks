#ifndef SLIDINGBLOCKS_INCLUDE_ENVIRONMENT_START_POINT_H_
#define SLIDINGBLOCKS_INCLUDE_ENVIRONMENT_START_POINT_H_

#include "environment/surface.h"
#include "game/game_component.h"

namespace sliding_blocks {

class StartPoint : public Surface {

 public:
  StartPoint(int id,
             int top_left_x,
             int top_left_y,
             int width,
             int height,
             SDL_Color color,
             GameComponent &game_component);
  int GetId();

 private:
  int id_;

};

}

#endif //SLIDINGBLOCKS_INCLUDE_ENVIRONMENT_START_POINT_H_
