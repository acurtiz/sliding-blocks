#include <SDL2/SDL.h>
#include "shape/rectangle.h"
#include "collider/rectangular_collider.h"
#include "game/living_unit.h"

#ifndef SLIDINGBLOCKS_INCLUDE_PLAYER_PLAYER_H_
#define SLIDINGBLOCKS_INCLUDE_PLAYER_PLAYER_H_

namespace sliding_blocks {

class Player : public Rectangle, public RectangularCollider, public LivingUnit {

 public:
  Player(SDL_Renderer *renderer, int width, int height, int top_left_x, int top_left_y);
  void HandleEvent(SDL_Event &event);
  void MoveCharacterSlide(uint32_t elapsed_millis);
  void MoveCharacterStraight(uint32_t elapsed_millis);
  void Render();
  void ResetMovement();

  // TODO: evaluate if/how we get rid of needing to maintain these more precise positions
  void SetTopLeftPosition(double x, double y);
  double GetPreciseTopLeftX() const;
  double GetPreciseTopLeftY() const;

  bool IsSliding() const;

 private:

  bool ShouldMoveToDestination() const;

  SDL_Renderer *renderer_;
  SDL_Color color_;

  double top_left_x_;
  double top_left_y_;

  int destination_x_;
  int destination_y_;
  double pixels_to_move_per_milli_; // speed
  double pixels_to_move_per_milli_x_;
  double pixels_to_move_per_milli_y_;
  double millis_remaining_to_reach_dest_;

  double player_angle_;
  double target_angle_;

  bool is_sliding_;

};

}

#endif //SLIDINGBLOCKS_INCLUDE_PLAYER_PLAYER_H_
