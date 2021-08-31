#include "shape/rectangle.h"

#ifndef SLIDINGBLOCKS_INCLUDE_COLLIDER_RECTANGULAR_COLLIDER_H_
#define SLIDINGBLOCKS_INCLUDE_COLLIDER_RECTANGULAR_COLLIDER_H_

namespace sliding_blocks {

class RectangularCollider {

 public:

  // We rely on and assume each object in our game can be represented by a single rectangle; as such, as simply
  // pass in the reference to the actual to-be-rendered rectangle, and then we don't need to continuously update it
  // in the actual object and in the collider
  RectangularCollider(Rectangle &rectangle);
  bool IsCollision(RectangularCollider &other);

 private:
  Rectangle &rectangle_;

};

}

#endif //SLIDINGBLOCKS_INCLUDE_COLLIDER_RECTANGULAR_COLLIDER_H_
