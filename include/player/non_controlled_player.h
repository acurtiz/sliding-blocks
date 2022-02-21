#ifndef SLIDINGBLOCKS_INCLUDE_PLAYER_NON_CONTROLLED_PLAYER_H_
#define SLIDINGBLOCKS_INCLUDE_PLAYER_NON_CONTROLLED_PLAYER_H_

#include <SDL2/SDL.h>
#include "shape/rectangle.h"
#include "collider/rectangular_collider.h"
#include "game/game_component.h"

namespace sliding_blocks {

class NonControlledPlayer : public Rectangle, public RectangularCollider, public GameComponent {

 public:
  NonControlledPlayer(GameComponent &game_component, int width, int height, int top_left_x, int top_left_y);
  void SetTopLeftPosition(double x, double y);
  void Render();

 private:
  SDL_Color color_;
  double top_left_x_;
  double top_left_y_;

};

}

#endif //SLIDINGBLOCKS_INCLUDE_PLAYER_NON_CONTROLLED_PLAYER_H_
