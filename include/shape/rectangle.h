#ifndef SLIDINGBLOCKS_INCLUDE_SHAPE_RECTANGLE_H_
#define SLIDINGBLOCKS_INCLUDE_SHAPE_RECTANGLE_H_

namespace sliding_blocks {

class Rectangle {

 public:
  Rectangle(int top_left_x, int top_left_y, int width, int height);
  virtual void SetTopLeftPosition(int x, int y);
  void SetWidth(int width);
  void SetHeight(int height);
  int GetTopLeftX() const;
  int GetTopLeftY() const;
  int GetWidth() const;
  int GetHeight() const;
  bool IsMouseInside() const;

 private:
  int top_left_x_;
  int top_left_y_;
  int width_;
  int height_;

};

}
#endif //SLIDINGBLOCKS_INCLUDE_SHAPE_RECTANGLE_H_
