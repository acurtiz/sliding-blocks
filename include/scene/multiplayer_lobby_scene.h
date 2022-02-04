#ifndef SLIDINGBLOCKS_INCLUDE_SCENE_MULTIPLAYER_LOBBY_SCENE_H_
#define SLIDINGBLOCKS_INCLUDE_SCENE_MULTIPLAYER_LOBBY_SCENE_H_

#include "scene/scene.h"
#include "text/text.h"
#include "button/rectangular_button.h"
#include "game/game_component.h"
#include "game/scene_executor.h"
#include "network/client.h"

namespace sliding_blocks {

class MultiplayerLobbyScene : public Scene {

 public:
  explicit MultiplayerLobbyScene(SceneExecutor
                                 &scene_executor,
                                 GameComponent &game_component);
  ~MultiplayerLobbyScene() override;
  void RunSingleIterationEventHandler(SDL_Event &event) override;
  void RunSingleIterationLoopBody() override;
  void PreSwitchHook() override;
  void PostSwitchHook() override;

 private:

  Text *title_;
  TTF_Font *title_font_;

  Text *connect_button_label_;
  RectangularButton *connect_button_;

  Text *start_button_label_;
  RectangularButton *start_button_;

  Text *quit_button_label_;
  RectangularButton *quit_button_;

  NetworkClient *network_client_;

};

}

#endif //SLIDINGBLOCKS_INCLUDE_SCENE_MULTIPLAYER_LOBBY_SCENE_H_
