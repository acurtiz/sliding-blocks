#include "enemy/straight_moving_enemy.h"
#include "environment/wall.h"

namespace sliding_blocks {

StraightMovingEnemy::StraightMovingEnemy(int top_left_x,
                                         int top_left_y,
                                         int width,
                                         int height,
                                         double velocity_x,
                                         double velocity_y,
                                         SDL_Color color,
                                         SDL_Renderer *renderer)
    : Rectangle(top_left_x, top_left_y, width, height),
      RectangularCollider((Rectangle &) *this),
      position_initial_((Rectangle &) *this),
      pixels_to_move_per_milli_x_initial_(velocity_x),
      pixels_to_move_per_milli_x_current_(velocity_x),
      pixels_to_move_per_milli_y_initial_(velocity_y),
      pixels_to_move_per_milli_y_current_(velocity_y),
      renderer_(renderer),
      color_(color) {}

void StraightMovingEnemy::Reset() {

  SetTopLeftPosition(position_initial_.GetTopLeftX(), position_initial_.GetTopLeftY());
  SetWidth(position_initial_.GetWidth());
  SetHeight(position_initial_.GetHeight());
  pixels_to_move_per_milli_x_current_ = pixels_to_move_per_milli_x_initial_;
  pixels_to_move_per_milli_y_current_ = pixels_to_move_per_milli_y_initial_;

}

void StraightMovingEnemy::Move(uint32_t elapsed_millis) {

  int pixels_to_move_x = (int) (pixels_to_move_per_milli_x_current_ * elapsed_millis);
  int pixels_to_move_y = (int) (pixels_to_move_per_milli_y_current_ * elapsed_millis);
  SetTopLeftPosition(GetTopLeftX() + pixels_to_move_x,
                     GetTopLeftY() + pixels_to_move_y);

}

void StraightMovingEnemy::UpdateIfCollision(RectangularCollider &other) {
  printf("UpdateIfCollision(RectangularCollider &other)\n");
}

void StraightMovingEnemy::UpdateIfCollision(Wall &other) {

  if (IsCollisionThisBottomWithOther(other) && pixels_to_move_per_milli_y_current_ > 0) {
    pixels_to_move_per_milli_y_current_ *= -1;
  } else if (IsCollisionThisTopWithOther(other) && pixels_to_move_per_milli_y_current_ < 0) {
    pixels_to_move_per_milli_y_current_ *= -1;
  }

  if (IsCollisionThisRightWithOther(other) && pixels_to_move_per_milli_x_current_ > 0) {
    pixels_to_move_per_milli_x_current_ *= -1;
  } else if (IsCollisionThisLeftWithOther(other) && pixels_to_move_per_milli_x_current_ < 0) {
    pixels_to_move_per_milli_x_current_ *= -1;
  }

}

void StraightMovingEnemy::Render() {
  // Get previous color
  SDL_Color previous_color;
  SDL_GetRenderDrawColor(renderer_, &previous_color.r, &previous_color.g, &previous_color.b, &previous_color.a);

  // Draw the object
  SDL_SetRenderDrawColor(renderer_, color_.r, color_.g, color_.b, color_.a);
  SDL_Rect rect = {GetTopLeftX(), GetTopLeftY(), GetWidth(), GetHeight()};
  SDL_RenderFillRect(renderer_, &rect);

  // Restore prior color
  SDL_SetRenderDrawColor(renderer_, previous_color.r, previous_color.g, previous_color.b, previous_color.a);
}

}

