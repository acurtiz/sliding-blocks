#include <SDL2_ttf/SDL_ttf.h>
#include <boost/format.hpp>
#include "pop_up_menu/death_menu.h"
#include "button/rectangular_button.h"
#include "button/button_event.h"
#include "text/text.h"
#include "scene/title_scene.h"

namespace sliding_blocks {

DeathMenu::DeathMenu(SDL_Renderer *renderer, int top_left_x, int top_left_y, int width, int height, Game &game)
    : PopUpMenu(renderer, top_left_x, top_left_y, width, height, {0x00, 0x00, 0x00, 0xFF}, game),
      renderer_(renderer),
      menu_title_(nullptr),
      font_(nullptr),
      label_main_menu_(nullptr),
      label_retry_(nullptr),
      button_main_menu_(nullptr),
      button_retry_(nullptr) {

  font_ = TTF_OpenFont("assets/font/OpenSans-Regular.ttf", 28);
  if (font_ == nullptr) {
    throw std::runtime_error(boost::str(boost::format("Failed to load font, error: %1%\n") % TTF_GetError()));
  }

  menu_title_ = new Text(renderer_, font_, {0xFF, 0xFF, 0xFF, 0xFF}, "Out of lives!");
  menu_title_->SetTopLeftPosition(GetTopLeftX() + GetWidth() / 2 - menu_title_->GetWidth() / 2, GetTopLeftY() + 50);
  label_main_menu_ = new Text(renderer_, font_, {0, 0, 0, 0xFF}, "Main Menu");
  label_retry_ = new Text(renderer_, font_, {0, 0, 0, 0xFF}, "Retry");

  int button_width = width / 2;
  int button_height = 75;
  int vertical_distance_between_buttons = 25;
  button_main_menu_ = new RectangularButton(GetTopLeftX() + GetWidth() / 2 - button_width / 2,
                                            menu_title_->GetTopLeftY() + menu_title_->GetHeight()
                                                + vertical_distance_between_buttons,
                                            button_width,
                                            button_height,
                                            label_main_menu_,
                                            renderer_);
  button_retry_ = new RectangularButton(button_main_menu_->GetTopLeftX(),
                                        button_main_menu_->GetTopLeftY() + button_main_menu_->GetHeight()
                                            + vertical_distance_between_buttons,
                                        button_width,
                                        button_height,
                                        label_retry_,
                                        renderer_);

}

DeathMenu::~DeathMenu() {
  delete menu_title_;

}

void DeathMenu::RunSingleIterationEventHandlerMenuContents(SDL_Event &event) {

  ButtonEvent event_main_menu_button = button_main_menu_->HandleEvent(&event);
  if (event_main_menu_button == PRESSED) {
    game_.SwitchScene(typeid(TitleScene));
  }

  ButtonEvent event_retry_button = button_retry_->HandleEvent(&event);
  if (event_retry_button == PRESSED) {

  }

}

void DeathMenu::RunSingleIterationLoopBodyMenuContents() {

  menu_title_->Render();
  button_main_menu_->Render();
  button_retry_->Render();

}

}

