#include "game/game_component.h"
#include "scene/scene.h"
#include "game/scene_executor.h"

namespace sliding_blocks {

Scene::Scene(SceneExecutor &scene_executor, GameComponent &game_component)
    : GameComponent(game_component),
      scene_executor_(scene_executor) {}

Scene::~Scene() = default;

}