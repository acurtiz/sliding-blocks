#include <cmath>
#include "player/player.h"

namespace sliding_blocks {

Player::Player(SDL_Renderer *renderer, int width, int height, int top_left_x, int top_left_y)
    : Rectangle(top_left_x, top_left_y, width, height),
      RectangularCollider((Rectangle &) *this),
      renderer_(renderer),
      velocity_(5),
      destination_x_(-1),
      destination_y_(-1),
      distance_(0),
      distance_x_(0),
      distance_y_(0),
      player_angle_(0),
      target_angle_(0),
      color_({0x00, 0x00, 0x00, 0xFF}) {
}

void Player::HandleEvent(SDL_Event &event) {

  if (event.type != SDL_MOUSEBUTTONDOWN) {
    return;
  }

  int mouse_x, mouse_y = 0;
  SDL_GetMouseState(&mouse_x, &mouse_y);

  destination_x_ = mouse_x;
  destination_y_ = mouse_y;

  // Otherwise, calculate distance to destination and set velocities
  distance_x_ = destination_x_ - GetTopLeftX();
  distance_y_ = destination_y_ - GetTopLeftY();
  distance_ = sqrt(pow(distance_x_, 2) + pow(distance_y_, 2));

  target_angle_ = atan2(distance_y_, distance_x_) * 180 / M_PI + 180;

}

void Player::MoveCharacterStraight() {

  // No destination has been set yet
  if (destination_x_ == -1 || destination_y_ == -1) {
    return;
  }

  // We only update coordinates (independently for x and y) if not yet close enough to destination
  bool update_x_coordinate = abs(destination_x_ - GetTopLeftX()) > 4;
  bool update_y_coordinate = abs(destination_y_ - GetTopLeftY()) > 4;

  SetTopLeftPosition(
      update_x_coordinate ? (int) (GetTopLeftX() + velocity_ * (distance_x_ / distance_)) : GetTopLeftX(),
      update_y_coordinate ? (int) (GetTopLeftY() + velocity_ * (distance_y_ / distance_)) : GetTopLeftY()
  );

  // Must update player angle so trajectory is maintained when transition to slick ground occurs
  player_angle_ = atan2(distance_y_, distance_x_) * 180 / M_PI + 180;

}

void Player::MoveCharacterSlide() {

  if (destination_x_ == -1 || destination_y_ == -1) {
    return;
  }

  player_angle_ = (int) player_angle_ % 360;

  // To figure out which direction to turn if target changes, normalize target angle
  double temp_angle = target_angle_ - player_angle_;
  if (temp_angle < 0) {
    temp_angle += 360;
  } else if (temp_angle > 360) {
    temp_angle -= 360;
  }

  // Change player angle based on location
  if (temp_angle < 180) {
    player_angle_ += 5;
  } else {
    player_angle_ -= 5;
  }

  // Update position based on angle
  SetTopLeftPosition(
      (int) (GetTopLeftX() + velocity_ * cos((player_angle_ - 180) * M_PI / 180)),
      (int) (GetTopLeftY() + velocity_ * sin((player_angle_ - 180) * M_PI / 180))
  );

}

void Player::ResetMovement() {

  destination_x_ = -1;
  destination_y_ = -1;
  distance_ = 0;
  distance_x_ = 0;
  distance_y_ = 0;
  player_angle_ = 0;
  target_angle_ = 0;

}

void Player::Render() {

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
