#include <SDL2_ttf/SDL_ttf.h>
#include <boost/format.hpp>
#include "scene/multiplayer_lobby_scene.h"
#include "scene/multiplayer_game_scene.h"
#include "game/game_component.h"
#include "game/scene_executor.h"

namespace sliding_blocks {

MultiplayerLobbyScene::MultiplayerLobbyScene(SceneExecutor &scene_executor, GameComponent &game_component)
    : Scene(scene_executor, game_component),
      title_(nullptr),
      connect_button_label_(nullptr),
      connect_button_(nullptr),
      start_button_label_(nullptr),
      start_button_(nullptr),
      quit_button_label_(nullptr),
      quit_button_(nullptr),
      network_client_(new NetworkClient()) {

  title_font_ = TTF_OpenFont("assets/font/OpenSans-Regular.ttf", 28);
  if (title_font_ == nullptr) {
    throw std::runtime_error(boost::str(boost::format("Failed to load font, error: %1%\n") % TTF_GetError()));
  }

  title_ = new Text(GetRenderer(), title_font_, {0xFF, 0xFF, 0xFF, 0xFF}, "Multiplayer Lobby", -1);
  title_->SetTopLeftPosition(GetScreenWidth() / 2 - title_->GetWidth() / 2,
                             100);

  connect_button_label_ = new Text(GetRenderer(), title_font_, {0xFF, 0xFF, 0xFF, 0xFF}, "Connect", -1);
  start_button_label_ = new Text(GetRenderer(), title_font_, {0xFF, 0xFF, 0xFF, 0xFF}, "Begin", -1);
  quit_button_label_ = new Text(GetRenderer(), title_font_, {0xFF, 0xFF, 0xFF, 0xFF}, "Exit", -1);

  int button_width =
      std::max({connect_button_label_->GetWidth(), start_button_label_->GetWidth(), quit_button_label_->GetWidth()})
          + 50;

  int button_height =
      std::max({connect_button_label_->GetHeight(), start_button_label_->GetHeight(), quit_button_label_->GetHeight()})
          + 40;

  connect_button_ = new RectangularButton(GetScreenWidth() / 2 - button_width / 2,
                                          title_->GetTopLeftY() + title_->GetHeight() + 20,
                                          button_width,
                                          button_height,
                                          connect_button_label_,
                                          *this);

  start_button_ = new RectangularButton(GetScreenWidth() / 2 - button_width / 2,
                                        connect_button_->GetTopLeftY() + connect_button_->GetHeight() + 20,
                                        button_width,
                                        button_height,
                                        start_button_label_,
                                        *this);

  quit_button_ = new RectangularButton(GetScreenWidth() / 2 - button_width / 2,
                                       start_button_->GetTopLeftY() + start_button_->GetHeight() + 20,
                                       button_width,
                                       button_height,
                                       quit_button_label_,
                                       *this);

}

MultiplayerLobbyScene::~MultiplayerLobbyScene() {

  delete title_;
  delete connect_button_;
  delete connect_button_label_;
  delete start_button_;
  delete start_button_label_;
  delete quit_button_;
  delete quit_button_label_;

  TTF_CloseFont(title_font_);

}

void MultiplayerLobbyScene::RunSingleIterationEventHandler(SDL_Event &event) {

  if (connect_button_->HandleEvent(&event) == PRESSED) {
    network_client_->Connect("localhost", 1337);
    network_client_->SendData();
    printf("Successfully connected\n");
  }

  if (start_button_->HandleEvent(&event) == PRESSED) {
    scene_executor_.SwitchScene(typeid(MultiplayerGameScene));
  }

  if (quit_button_->HandleEvent(&event) == PRESSED) {
    scene_executor_.Quit();
  }

}

void MultiplayerLobbyScene::RunSingleIterationLoopBody() {

  SDL_SetRenderDrawColor(GetRenderer(), 0x00, 0x00, 0x00, 0xFF);
  SDL_RenderClear(GetRenderer());

  title_->Render();
  connect_button_->Render();
  start_button_->Render();
  quit_button_->Render();
  SDL_RenderPresent(GetRenderer());

}

void MultiplayerLobbyScene::PreSwitchHook() {}

void MultiplayerLobbyScene::PostSwitchHook() {}

}

