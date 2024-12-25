#include <SDL2/SDL_ttf.h>
#include <boost/format.hpp>
#include <utility>
#include "pop_up_menu/death_menu.h"
#include "button/rectangular_button.h"

#include "text/text.h"

namespace sliding_blocks {

DeathMenu::DeathMenu(GameComponent &game_component,
                     std::function<void()> main_menu_callback,
                     std::function<void()> retry_callback)
    : PopUpMenu((int) (game_component.GetScreenWidth() * 0.1),
                (int) (game_component.GetScreenHeight() * 0.2),
                (int) (game_component.GetScreenWidth() * 0.8),
                (int) (game_component.GetScreenHeight() * 0.6),
                {0x11, 0x11, 0x11, 0xFF},
                game_component),
      main_menu_callback_(std::move(main_menu_callback)),
      retry_callback_(std::move(retry_callback)),
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

  menu_title_ = new Text(GetRenderer(), font_, {0xFF, 0xFF, 0xFF, 0xFF}, "Out of lives!");
  menu_title_->SetTopLeftPosition(GetTopLeftX() + GetWidth() / 2 - menu_title_->GetWidth() / 2, GetTopLeftY() + 50);
  label_main_menu_ = new Text(GetRenderer(), font_, {0, 0, 0, 0xFF}, "Main Menu");
  label_retry_ = new Text(GetRenderer(), font_, {0, 0, 0, 0xFF}, "Retry");

  int button_width = GetWidth() / 2;
  int button_height = 50;
  int vertical_distance_between_buttons = 25;
  button_main_menu_ = new RectangularButton(GetTopLeftX() + GetWidth() / 2 - button_width / 2,
                                            menu_title_->GetTopLeftY() + menu_title_->GetHeight()
                                                + vertical_distance_between_buttons,
                                            button_width,
                                            button_height,
                                            label_main_menu_,
                                            *this);
  button_retry_ = new RectangularButton(button_main_menu_->GetTopLeftX(),
                                        button_main_menu_->GetTopLeftY() + button_main_menu_->GetHeight()
                                            + vertical_distance_between_buttons,
                                        button_width,
                                        button_height,
                                        label_retry_,
                                        *this);

}

DeathMenu::~DeathMenu() {

  delete menu_title_;
  delete label_main_menu_;
  delete label_retry_;
  delete button_main_menu_;
  delete button_retry_;
  TTF_CloseFont(font_);

}

void DeathMenu::RunSingleIterationEventHandlerMenuContents(SDL_Event &event) {

  ButtonEvent event_main_menu_button = button_main_menu_->HandleEvent(&event);
  ButtonEvent event_retry_button = button_retry_->HandleEvent(&event);

  if (event_main_menu_button == PRESSED) {
    main_menu_callback_();
  } else if (event_retry_button == PRESSED) {
    retry_callback_();
  }

}

void DeathMenu::RunSingleIterationLoopBodyMenuContents() {

  menu_title_->Render();
  button_main_menu_->Render();
  button_retry_->Render();

}

}

