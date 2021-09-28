#ifndef SLIDINGBLOCKS_INCLUDE_COLLIDER_RECTANGULAR_COLLIDER_H_
#define SLIDINGBLOCKS_INCLUDE_COLLIDER_RECTANGULAR_COLLIDER_H_

#include "shape/rectangle.h"

namespace sliding_blocks {

class RectangularCollider {

 public:

  // We rely on and assume each object in our game can be represented by a single rectangle; as such, as simply
  // pass in the reference to the actual to-be-rendered rectangle, and then we don't need to continuously update it
  // in the actual object and in the collider
  explicit RectangularCollider(Rectangle &rectangle);
  bool IsCollision(RectangularCollider &other);
  bool IsCollisionThisLeftWithOther(RectangularCollider &other);
  bool IsCollisionThisRightWithOther(RectangularCollider &other);
  bool IsCollisionThisTopWithOther(RectangularCollider &other);
  bool IsCollisionThisBottomWithOther(RectangularCollider &other);

  template<typename Container>
  bool IsCollision(Container &container);

  template<typename ReturnType, typename Container>
  ReturnType GetCollidingObject(Container &container);

 private:
  Rectangle &rectangle_;

};

template<typename Container>
bool RectangularCollider::IsCollision(Container &container) {

  for (typename Container::iterator it = container.begin(); it != container.end(); ++it) {
    RectangularCollider *other = (RectangularCollider *) *it;
    if (IsCollision(*other)) {
      return true;
    }
  }

  return false;
}

template<typename ReturnType, typename Container>
ReturnType RectangularCollider::GetCollidingObject(Container &container) {

  for (typename Container::iterator it = container.begin(); it != container.end(); ++it) {
    RectangularCollider *other = (RectangularCollider *) *it;
    if (IsCollision(*other)) {
      return *it;
    }
  }

  return nullptr;
}

}

#endif //SLIDINGBLOCKS_INCLUDE_COLLIDER_RECTANGULAR_COLLIDER_H_
