#include <SDL2/SDL.h>
#include "shape/rectangle.h"
#include "collider/rectangular_collider.h"

#ifndef SLIDINGBLOCKS_INCLUDE_PLAYER_PLAYER_H_
#define SLIDINGBLOCKS_INCLUDE_PLAYER_PLAYER_H_

namespace sliding_blocks {

class Player : public Rectangle, public RectangularCollider {

 public:
  Player(SDL_Renderer *renderer, int width, int height, int top_left_x, int top_left_y);
  void HandleEvent(SDL_Event &event);
  void MoveCharacterSlide();
  void MoveCharacterStraight();
  void Render();

 private:

  SDL_Renderer *renderer_;
  SDL_Color color_;

  int destination_x_;
  int destination_y_;
  double distance_x_;
  double distance_y_;
  double distance_;
  double velocity_; // pixels per frame
  double player_angle_;
  double target_angle_;

};

}

#endif //SLIDINGBLOCKS_INCLUDE_PLAYER_PLAYER_H_
