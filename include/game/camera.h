#ifndef SLIDINGBLOCKS_INCLUDE_GAME_CAMERA_H_
#define SLIDINGBLOCKS_INCLUDE_GAME_CAMERA_H_

#include "shape/rectangle.h"

namespace sliding_blocks {

class Camera : public Rectangle {

 public:
  Camera(int width, int height, int top_left_x, int top_left_y);
  void SetBoundaries(int top, int right, int bottom, int left);
  void CenterOnObject(Rectangle &obj);

 private:
  int boundary_left_x_;
  int boundary_right_x_;
  int boundary_top_y_;
  int boundary_bottom_y_;

};

}

#endif //SLIDINGBLOCKS_INCLUDE_GAME_CAMERA_H_
