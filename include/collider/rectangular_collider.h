#include "shape/rectangle.h"

#ifndef SLIDINGBLOCKS_INCLUDE_COLLIDER_RECTANGULAR_COLLIDER_H_
#define SLIDINGBLOCKS_INCLUDE_COLLIDER_RECTANGULAR_COLLIDER_H_

namespace sliding_blocks {

class RectangularCollider {

 public:

  // We rely on and assume each object in our game can be represented by a single rectangle; as such, as simply
  // pass in the reference to the actual to-be-rendered rectangle, and then we don't need to continuously update it
  // in the actual object and in the collider
  explicit RectangularCollider(Rectangle &rectangle);
  bool IsCollision(RectangularCollider &other);

  template<typename InputIterator>
  bool IsCollision(InputIterator begin, InputIterator end);

 private:
  Rectangle &rectangle_;

};

template<typename InputIterator>
bool RectangularCollider::IsCollision(InputIterator begin, InputIterator end) {

  for (InputIterator it = begin; it != end; ++it) {
    RectangularCollider *other = (RectangularCollider *) *it;
    if (IsCollision(*other)) {
      return true;
    }
  }

  return false;
}

}

#endif //SLIDINGBLOCKS_INCLUDE_COLLIDER_RECTANGULAR_COLLIDER_H_
