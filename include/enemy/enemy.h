#include "shape/rectangle.h"
#include "environment/surface.h"
#include "collider/rectangular_collider.h"
#include "environment/wall.h"

#ifndef SLIDINGBLOCKS_INCLUDE_ENEMY_ENEMY_H_
#define SLIDINGBLOCKS_INCLUDE_ENEMY_ENEMY_H_

namespace sliding_blocks {

class Enemy : public virtual Rectangle, public virtual RectangularCollider {

 public:
  virtual ~Enemy() = default;
  virtual void Reset() = 0;
  virtual void UpdateIfCollision(RectangularCollider &other) = 0;
  virtual void UpdateIfCollision(Wall &other) = 0;
  virtual void Move(uint32_t elapsed_millis) = 0;
  virtual void Render() = 0;
};

}

#endif //SLIDINGBLOCKS_INCLUDE_ENEMY_ENEMY_H_
