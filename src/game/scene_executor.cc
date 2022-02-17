#include <SDL2/SDL.h>
#include "game/game_component.h"
#include "game/scene_executor.h"
#include "scene/game_scene.h"
#include "scene/title_scene.h"
#include "scene/multiplayer_lobby_scene.h"
#include "scene/multiplayer_game_scene.h"
#include "network/client.h"

namespace sliding_blocks {

SceneExecutor::SceneExecutor(GameComponent &game_object)
    : GameComponent(game_object),
      scene_current_(nullptr),
      scene_next_(nullptr),
      should_quit_(false),
      network_client_(NetworkClient()) {

  LoadScenes();

}

SceneExecutor::~SceneExecutor() {

  UnloadScenes();

}

void SceneExecutor::Run() {

  scene_next_ = type_to_scene_map_[typeid(TitleScene)];

  SDL_Event event;

  while (!should_quit_) {

    if (scene_next_ != nullptr) {
      if (scene_current_ != nullptr) {
        scene_current_->PostSwitchHook();
      }
      scene_current_ = scene_next_;
      scene_next_ = nullptr;
      scene_current_->PreSwitchHook();
    }

    while (SDL_PollEvent(&event)) {

      if (should_quit_) {
        return;
      }

      if (event.type == SDL_QUIT) {
        Quit();
      }

      scene_current_->RunSingleIterationEventHandler(event);
    }

    if (should_quit_) {
      return;
    }

    scene_current_->RunSingleIterationLoopBody();

    SDL_Delay(15);
  }

}

void SceneExecutor::SwitchScene(std::type_index scene_type) {

  auto scene_to_switch_to = type_to_scene_map_.find(scene_type);
  if (scene_to_switch_to == type_to_scene_map_.end()) {
    throw std::runtime_error("Scene not found\n");
  }

  scene_next_ = scene_to_switch_to->second;

}

void SceneExecutor::LoadScenes() {

  auto *title_scene = new TitleScene(*this, *this);
  auto *game_scene = new GameScene(*this, *this);
  auto *multiplayer_lobby_scene = new MultiplayerLobbyScene(*this, *this, network_client_);
  auto *multiplayer_game_scene = new MultiplayerGameScene(*this, *this, network_client_);
  type_to_scene_map_[typeid(TitleScene)] = title_scene;
  type_to_scene_map_[typeid(GameScene)] = game_scene;
  type_to_scene_map_[typeid(MultiplayerLobbyScene)] = multiplayer_lobby_scene;
  type_to_scene_map_[typeid(MultiplayerGameScene)] = multiplayer_game_scene;

}

void SceneExecutor::UnloadScenes() {

  for (auto &entry: type_to_scene_map_) {
    delete entry.second;
  }

}

void SceneExecutor::Quit() {
  should_quit_ = true;
}

}

