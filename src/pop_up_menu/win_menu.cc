#include <SDL2_ttf/SDL_ttf.h>
#include <boost/format.hpp>
#include <utility>
#include "pop_up_menu/win_menu.h"
#include "button/rectangular_button.h"
#include "text/text.h"

namespace sliding_blocks {

WinMenu::WinMenu(GameComponent &game_component,
                 std::function<void()> main_menu_callback)
    : PopUpMenu((int) (game_component.GetScreenWidth() * 0.1),
                (int) (game_component.GetScreenHeight() * 0.2),
                (int) (game_component.GetScreenWidth() * 0.8),
                (int) (game_component.GetScreenHeight() * 0.6),
                {0x00, 0x00, 0x00, 0xFF},
                game_component),
      main_menu_callback_(std::move(main_menu_callback)),
      menu_title_(nullptr),
      font_(nullptr),
      label_main_menu_(nullptr),
      button_main_menu_(nullptr) {

  font_ = TTF_OpenFont("assets/font/OpenSans-Regular.ttf", 28);
  if (font_ == nullptr) {
    throw std::runtime_error(boost::str(boost::format("Failed to load font, error: %1%\n") % TTF_GetError()));
  }

  menu_title_ = new Text(GetRenderer(), font_, {0xFF, 0xFF, 0xFF, 0xFF}, "You win! Well done.");
  menu_title_->
      SetTopLeftPosition(GetTopLeftX() + GetWidth() / 2 - menu_title_->GetWidth() / 2, GetTopLeftY() + 50);
  label_main_menu_ = new Text(GetRenderer(), font_, {0, 0, 0, 0xFF}, "Main Menu");

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

}

WinMenu::~WinMenu() {

  delete menu_title_;
  delete label_main_menu_;
  delete button_main_menu_;
  TTF_CloseFont(font_);

}

void WinMenu::RunSingleIterationEventHandlerMenuContents(SDL_Event &event) {

  ButtonEvent event_main_menu_button = button_main_menu_->HandleEvent(&event);

  if (event_main_menu_button == PRESSED) {
    main_menu_callback_();
  }

}

void WinMenu::RunSingleIterationLoopBodyMenuContents() {

  menu_title_->Render();
  button_main_menu_->Render();

}

}

