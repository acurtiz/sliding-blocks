#include "button/rectangular_button.h"

namespace sliding_blocks {

RectangularButton::RectangularButton(int top_left_x,
                                     int top_left_y,
                                     int width,
                                     int height,
                                     Text *label,
                                     SDL_Renderer *renderer)
    : Rectangle(top_left_x, top_left_y, width, height),
      label_(label),
      renderer_(renderer),
      current_color_(&color_default_) {}

ButtonEvent RectangularButton::HandleEvent(SDL_Event *event) {

  if (!(event->type == SDL_MOUSEMOTION || event->type == SDL_MOUSEBUTTONDOWN || event->type == SDL_MOUSEBUTTONUP)) {
    return NONE;
  }

  current_color_ = &color_default_;

  if (IsMouseInside()) {

    switch (event->type) {
      case SDL_MOUSEBUTTONDOWN:
        current_color_ = &color_mouse_down_;
        break;
      case SDL_MOUSEMOTION:
        current_color_ = &color_mouse_motion_;
        break;
      case SDL_MOUSEBUTTONUP:
        return PRESSED;
      default:
        printf("Unrecognized mouse event type: %d", event->type);
        return NONE;
    }
  }

  return NONE;

}

void RectangularButton::SetTopLeftPosition(int top_left_x, int top_left_y) {

  Rectangle::SetTopLeftPosition(top_left_x, top_left_y);

  int extra_width = GetWidth() - label_->GetWidth();
  int extra_height = GetHeight() - label_->GetHeight();

  if (extra_width < 0) {
    printf("Warning: button width (%d) is less than label width (%d), yet button needs to hold entire label\n",
           GetWidth(),
           label_->GetWidth());
  }

  if (extra_height < 0) {
    printf("Warning: button height (%d) is less than label width (%d), yet button needs to hold entire label\n",
           GetHeight(),
           label_->GetHeight());
  }

  int label_top_left_x = GetTopLeftX() + extra_width / 2;
  int label_top_left_y = GetTopLeftY() + extra_height / 2;

  label_->SetTopLeftPosition(label_top_left_x, label_top_left_y);

}

void RectangularButton::Render() {

  // Get previous color
  SDL_Color previous_color;
  SDL_GetRenderDrawColor(renderer_, &previous_color.r, &previous_color.g, &previous_color.b, &previous_color.a);

  SDL_Rect rect = {GetTopLeftX(), GetTopLeftY(), GetWidth(), GetHeight()};
  SDL_SetRenderDrawColor(renderer_, current_color_->r, current_color_->g, current_color_->b, current_color_->a);
  SDL_RenderFillRect(renderer_, &rect);
  label_->Render();

  // Restore prior color
  SDL_SetRenderDrawColor(renderer_, previous_color.r, previous_color.g, previous_color.b, previous_color.a);

}

}