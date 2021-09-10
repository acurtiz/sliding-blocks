#include "environment/surface.h"

#ifndef SLIDINGBLOCKS_INCLUDE_ENVIRONMENT_END_POINT_H_
#define SLIDINGBLOCKS_INCLUDE_ENVIRONMENT_END_POINT_H_

namespace sliding_blocks {

class EndPoint : public Surface {

 public:
  EndPoint(int id, int top_left_x, int top_left_y, int width, int height, SDL_Renderer *renderer);
  int GetId();

 private:
  int id_;

};

}

#endif //SLIDINGBLOCKS_INCLUDE_ENVIRONMENT_END_POINT_H_
