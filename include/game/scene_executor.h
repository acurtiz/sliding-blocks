#ifndef SLIDINGBLOCKS_INCLUDE_GAME_SCENE_EXECUTOR_H_
#define SLIDINGBLOCKS_INCLUDE_GAME_SCENE_EXECUTOR_H_

#include <typeindex>
#include <map>
#include <SDL2/SDL.h>
#include "scene/scene.h"
#include "game/game_component.h"

namespace sliding_blocks {

class SceneExecutor : public GameComponent {

 public:
  explicit SceneExecutor(GameComponent &game_object);
  ~SceneExecutor();
  void Run();
  void SwitchScene(std::type_index scene_type);
  void Quit();

 private:
  void LoadScenes();
  void UnloadScenes();
  std::map<std::type_index, Scene *> type_to_scene_map_;
  Scene *scene_current_;
  Scene *scene_next_;
  bool should_quit_;
};

}

#endif //SLIDINGBLOCKS_INCLUDE_GAME_SCENE_EXECUTOR_H_
