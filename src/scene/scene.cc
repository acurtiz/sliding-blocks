#include "game/game.h"
#include "scene/scene.h"

namespace sliding_blocks {

Scene::Scene(Game &game)
    : game_(game) {}

Scene::~Scene() = default;

}