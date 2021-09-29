#include <cmath>
#include "player/player.h"
#include "util/trig.h"

namespace sliding_blocks {

Player::Player(GameComponent &game_component, int width, int height, int top_left_x, int top_left_y)
    : Rectangle(top_left_x, top_left_y, width, height),
      RectangularCollider((Rectangle &) *this),
      LivingUnit(3),
      GameComponent(game_component),
      top_left_x_(top_left_x),
      top_left_y_(top_left_y),
      destination_x_(-1),
      destination_y_(-1),
      pixels_to_move_per_milli_x_(0),
      pixels_to_move_per_milli_y_(0),
      millis_remaining_to_reach_dest_(0),
      pixels_to_move_per_milli_(0.3),
      player_angle_(0),
      target_angle_(0),
      is_sliding_(false),
      color_({0x00, 0x00, 0x00, 0xFF}) {
}

void Player::SetTopLeftPosition(double x, double y) {
  Rectangle::SetTopLeftPosition((int) x, (int) y);
  top_left_x_ = x;
  top_left_y_ = y;
}

double Player::GetPreciseTopLeftX() const {
  return top_left_x_;
}

double Player::GetPreciseTopLeftY() const {
  return top_left_y_;
}

void Player::HandleEvent(SDL_Event &event) {

  if (event.type != SDL_MOUSEBUTTONDOWN) {
    return;
  }

  SDL_GetMouseState(&destination_x_, &destination_y_);

  // World coordinates (actual destination) == screen coordinates (i.e. mouse state) + camera offset
  destination_x_ = destination_x_ + GetCamera()->GetTopLeftX();
  destination_y_ = destination_y_ + GetCamera()->GetTopLeftY();

  // We get the unit vector from player to destination, and combine that with the speed to get the velocity vector
  // (in pixels per millisecond); then we calculate the time it will take to reach the destination. The per-frame loop
  // thus has everything required to control changing position for non-slick straight line movement
  double distance_x = destination_x_ - GetPreciseTopLeftX();
  double distance_y = destination_y_ - GetPreciseTopLeftY();
  double total_distance = sqrt(pow(distance_x, 2) + pow(distance_y, 2));
  double normalized_distance_x = distance_x / total_distance;
  double normalized_distance_y = distance_y / total_distance;
  pixels_to_move_per_milli_x_ = normalized_distance_x * pixels_to_move_per_milli_;
  pixels_to_move_per_milli_y_ = normalized_distance_y * pixels_to_move_per_milli_;
  millis_remaining_to_reach_dest_ = total_distance / pixels_to_move_per_milli_;

  // For slick movement, we must calculate the target angle, which is the angle between the destination and the player
  target_angle_ =
      Trig::ConvertRadiansToDegrees(Trig::NormalizeRadiansBetweenZeroAndTwoPi(atan2(distance_y, distance_x)));

}

void Player::MoveCharacterStraight(uint32_t elapsed_millis) {

  if (!ShouldMoveToDestination()) {
    return;
  }

  if (millis_remaining_to_reach_dest_ <= elapsed_millis) {
    millis_remaining_to_reach_dest_ = 0;
    SetTopLeftPosition(destination_x_, destination_y_);
    return;
  }

  millis_remaining_to_reach_dest_ -= elapsed_millis;
  double pixels_to_move_x = pixels_to_move_per_milli_x_ * elapsed_millis;
  double pixels_to_move_y = pixels_to_move_per_milli_y_ * elapsed_millis;

  SetTopLeftPosition(GetPreciseTopLeftX() + pixels_to_move_x,
                     GetPreciseTopLeftY() + pixels_to_move_y);

  // Must update player angle so trajectory is maintained when transition to slick ground occurs
  player_angle_ = Trig::ConvertRadiansToDegrees(Trig::NormalizeRadiansBetweenZeroAndTwoPi(atan2(pixels_to_move_y,
                                                                                                pixels_to_move_x)));

}

void Player::MoveCharacterSlide(uint32_t elapsed_millis) {

  if (!ShouldMoveToDestination()) {
    return;
  }

  is_sliding_ = true;

  // Ensure player angle is between 0 and 360 always
  player_angle_ = (int) Trig::NormalizeDegrees(player_angle_);

  // We must find the target angle relative to the player angle (i.e. we've normalized so player angle is 0)
  // Once we've done that, if that normalized target angle is in upper half of unit circle, we need to increase
  // player angle (to reduce the gap most effectively - decreasing would eventually eliminate the gap, but would be
  // slower). Conversely, if that normalized target is in the lower half, we need to decrease
  // the player angle to make the player angle meet the target angle as quickly as possible.
  // target angle - player angle is guaranteed to be within [-360, 360]; with addition and modulus, we shift the
  // result to be [0, 360], which still lets us determine the exact quadrant
  auto target_angle_relative_to_player_angle = (int) Trig::NormalizeDegrees(target_angle_ - player_angle_);
  bool should_increase_player_angle = target_angle_relative_to_player_angle < 180;

  player_angle_ = should_increase_player_angle ?
                  player_angle_ + 5 :
                  player_angle_ - 5;

  SetTopLeftPosition(
      (int) (GetTopLeftX()
          + pixels_to_move_per_milli_ * elapsed_millis * cos(Trig::ConvertDegreesToRadians(player_angle_))),
      (int) (GetTopLeftY()
          + pixels_to_move_per_milli_ * elapsed_millis * sin(Trig::ConvertDegreesToRadians(player_angle_)))
  );

}

void Player::ResetMovement() {

  destination_x_ = -1;
  destination_y_ = -1;
  millis_remaining_to_reach_dest_ = 0;
  pixels_to_move_per_milli_y_ = 0;
  pixels_to_move_per_milli_x_ = 0;
  player_angle_ = 0;
  target_angle_ = 0;
  is_sliding_ = false;

}

void Player::Render() {

  // Get previous color
  SDL_Color previous_color;
  SDL_GetRenderDrawColor(GetRenderer(), &previous_color.r, &previous_color.g, &previous_color.b, &previous_color.a);

  // Draw the object
  SDL_SetRenderDrawColor(GetRenderer(), color_.r, color_.g, color_.b, color_.a);
  SDL_Rect rect = {
      GetTopLeftX() - GetCamera()->GetTopLeftX(),
      GetTopLeftY() - GetCamera()->GetTopLeftY(),
      GetWidth(),
      GetHeight()
  };
  SDL_RenderFillRect(GetRenderer(), &rect);

  // Restore prior color
  SDL_SetRenderDrawColor(GetRenderer(), previous_color.r, previous_color.g, previous_color.b, previous_color.a);
}

bool Player::IsSliding() const {
  return is_sliding_;
}

bool Player::ShouldMoveToDestination() const {

  if (destination_x_ == -1 && destination_y_ == -1) {
    return false;
  }

  return true;

}

}
