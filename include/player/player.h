#include <SDL2/SDL.h>

#ifndef SLIDINGBLOCKS_INCLUDE_PLAYER_PLAYER_H_
#define SLIDINGBLOCKS_INCLUDE_PLAYER_PLAYER_H_

namespace sliding_blocks {

class Player {

 public:
  Player(SDL_Renderer *renderer, int width, int height, int top_left_x, int top_left_y);
  void HandleEvent(SDL_Event &event);
  void ProcessFrame();
  void SetTopLeftPosition(int x, int y);
  int GetTopLeftX() const;
  int GetTopLeftY() const;
  void Render();

 private:

  void MoveCharacterSlide();
  void MoveCharacterStraight();

  SDL_Renderer *renderer_;
  SDL_Color color_ = {0xFF, 0xFF, 0xFF, 0xFF};
  int top_left_x_;
  int top_left_y_;
  int width_;
  int height_;
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
