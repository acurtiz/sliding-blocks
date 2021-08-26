#include <cmath>
#include "player/player.h"

namespace sliding_blocks {

Player::Player(SDL_Renderer *renderer, int width, int height, int top_left_x, int top_left_y)
    : renderer_(renderer),
      width_(width),
      height_(height),
      velocity_(10),
      top_left_x_(top_left_x),
      top_left_y_(top_left_y),
      destination_x_(-1),
      destination_y_(-1),
      distance_(0),
      distance_x_(0),
      distance_y_(0),
      player_angle_(0),
      target_angle_(0) {
}

void Player::HandleEvent(SDL_Event &event) {

  if (event.type != SDL_MOUSEBUTTONDOWN) {
    return;
  }

  printf("Handling event!\n");

  int mouse_x, mouse_y = 0;
  SDL_GetMouseState(&mouse_x, &mouse_y);

  destination_x_ = mouse_x;
  destination_y_ = mouse_y;

  // Otherwise, calculate distance to destination and set velocities
  distance_x_ = destination_x_ - top_left_x_;
  distance_y_ = destination_y_ - top_left_y_;
  distance_ = sqrt(pow(distance_x_, 2) + pow(distance_y_, 2));

  target_angle_ = atan2(distance_y_, distance_x_) * 180 / M_PI + 180;
  printf("Target angle: %f\n", target_angle_);

}

void Player::ProcessFrame() {

  bool should_move_straight = false;

  if (should_move_straight) {
    MoveCharacterStraight();
  } else {
    MoveCharacterSlide();
  }
}

void Player::MoveCharacterStraight() {

  // No destination has been set yet
  if (destination_x_ == -1 || destination_y_ == -1) {
    return;
  }

  // Once close enough to the destination, we stop moving
  if (abs(destination_x_ - top_left_x_) > 4) {
    top_left_x_ = (int) (top_left_x_ + velocity_ * (distance_x_ / distance_));
  }
  if (abs(destination_y_ - top_left_y_) > 4) {
    top_left_y_ = (int) (top_left_y_ + velocity_ * (distance_y_ / distance_));
  }

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
  top_left_y_ = (int) (top_left_y_ + velocity_ * sin((player_angle_ - 180) * M_PI / 180));
  top_left_x_ = (int) (top_left_x_ + velocity_ * cos((player_angle_ - 180) * M_PI / 180));

}

void Player::Render() {

  // Get previous color
  SDL_Color previous_color;
  SDL_GetRenderDrawColor(renderer_, &previous_color.r, &previous_color.g, &previous_color.b, &previous_color.a);

  // Draw the object
  SDL_SetRenderDrawColor(renderer_, color_.r, color_.g, color_.b, color_.a);
  SDL_Rect rect = {top_left_x_, top_left_y_, width_, height_};
  SDL_RenderFillRect(renderer_, &rect);
  SDL_RenderPresent(renderer_);

  // Restore prior color
  SDL_SetRenderDrawColor(renderer_, previous_color.r, previous_color.g, previous_color.b, previous_color.a);
}

void Player::SetTopLeftPosition(int x, int y) {
  top_left_x_ = x;
  top_left_y_ = y;
}

int Player::GetTopLeftY() const {
  return top_left_y_;
}

int Player::GetTopLeftX() const {
  return top_left_x_;
}

}
