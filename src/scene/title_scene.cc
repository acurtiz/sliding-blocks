#include <SDL2_ttf/SDL_ttf.h>
#include <boost/format.hpp>
#include "scene/title_scene.h"
#include "scene/game_scene.h"

namespace sliding_blocks {

TitleScene::TitleScene(SDL_Renderer *renderer, SDL_Window *window, bool &global_quit)
    : Scene(renderer, window, global_quit),
      title_(nullptr),
      start_button_label_(nullptr),
      start_button_(nullptr),
      quit_button_label_(nullptr),
      quit_button_(nullptr) {

  title_font_ = TTF_OpenFont("assets/font/OpenSans-Regular.ttf", 28);
  if (title_font_ == nullptr) {
    throw std::runtime_error(boost::str(boost::format("Failed to load font, error: %1%\n") % TTF_GetError()));
  }

}

TitleScene::~TitleScene() {

  TTF_CloseFont(title_font_);

}

void TitleScene::RunPreLoop() {

  title_ = new Text(renderer_, title_font_, {0xFF, 0xFF, 0xFF, 0xFF}, "Sliding Blocks!", -1);
  title_->SetTopLeftPosition(GetScreenWidth() / 2 - title_->GetWidth() / 2,
                             100);

  start_button_label_ = new Text(renderer_, title_font_, {0xFF, 0xFF, 0xFF, 0xFF}, "Begin", -1);
  quit_button_label_ = new Text(renderer_, title_font_, {0xFF, 0xFF, 0xFF, 0xFF}, "Exit", -1);

  int button_width = start_button_label_->GetWidth() > quit_button_label_->GetWidth()
                     ? start_button_label_->GetWidth() + 50 : quit_button_label_->GetWidth() + 50;
  int button_height = start_button_label_->GetHeight() > quit_button_label_->GetHeight()
                      ? start_button_label_->GetHeight() + 40 : quit_button_label_->GetWidth() + 40;

  start_button_ = new RectangularButton(0,
                                        0,
                                        button_width,
                                        button_height,
                                        start_button_label_,
                                        renderer_);
  start_button_->SetTopLeftPosition(GetScreenWidth() / 2 - start_button_->GetWidth() / 2,
                                    title_->GetTopLeftY() + title_->GetHeight() + 20);

  quit_button_ = new RectangularButton(0,
                                       0,
                                       button_width,
                                       button_height,
                                       quit_button_label_,
                                       renderer_);
  quit_button_->SetTopLeftPosition(GetScreenWidth() / 2 - quit_button_->GetWidth() / 2,
                                   start_button_->GetTopLeftY() + start_button_->GetHeight() + 20);

}

void TitleScene::RunPostLoop() {

  delete title_;
  delete start_button_;
  delete start_button_label_;
  delete quit_button_;
  delete quit_button_label_;

}

void TitleScene::RunSingleIterationEventHandler(SDL_Event &event) {

  if (start_button_->HandleEvent(&event) == PRESSED) {
    GameScene game_scene(renderer_, window_, global_quit_);
    game_scene.Run();
  }

  if (quit_button_->HandleEvent(&event) == PRESSED) {
    QuitGlobal();
  }

}

void TitleScene::RunSingleIterationLoopBody() {

  SDL_SetRenderDrawColor(renderer_, 0x00, 0x00, 0x00, 0xFF);
  SDL_RenderClear(renderer_);

  title_->Render();
  start_button_->Render();
  quit_button_->Render();
  SDL_RenderPresent(renderer_);

}

}

