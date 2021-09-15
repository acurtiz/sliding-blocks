#include <SDL2/SDL.h>
#include "enemy/enemy.h"
#include "collider/rectangular_collider.h"
#include "environment/surface.h"

#ifndef SLIDINGBLOCKS_INCLUDE_ENEMY_STRAIGHT_MOVING_ENEMY_H_
#define SLIDINGBLOCKS_INCLUDE_ENEMY_STRAIGHT_MOVING_ENEMY_H_

namespace sliding_blocks {

class StraightMovingEnemy : public Enemy {

 public:
  StraightMovingEnemy(int top_left_x,
                      int top_left_y,
                      int width,
                      int height,
                      double velocity_x,
                      double velocity_y,
                      SDL_Color color,
                      SDL_Renderer *renderer);

  void Reset() override;
  void UpdateIfCollision(RectangularCollider &other) override;
  void UpdateIfCollision(Surface &other) override;
  void Move(uint32_t elapsed_millis) override;
  void Render() override;

 private:
  double const pixels_to_move_per_milli_x_initial_;
  double const pixels_to_move_per_milli_y_initial_;
  double pixels_to_move_per_milli_x_current_;
  double pixels_to_move_per_milli_y_current_;
  Rectangle const position_initial_;
  SDL_Renderer *renderer_;
  SDL_Color color_;

};

}

#endif //SLIDINGBLOCKS_INCLUDE_ENEMY_STRAIGHT_MOVING_ENEMY_H_
