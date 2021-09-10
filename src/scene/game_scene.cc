#include "scene/game_scene.h"
#include "player/player.h"
#include "environment/surface.h"

namespace sliding_blocks {

GameScene::GameScene(SDL_Renderer *renderer,
                     SDL_Window *window,
                     bool &global_quit,
                     int screen_height,
                     int screen_width)
    : Scene(renderer, window, global_quit),
      screen_height_(screen_width),
      screen_width_(screen_width),
      player_(nullptr) {

}

void GameScene::RunPreLoop() {

  player_ = new Player(renderer_, 10, 10, 10, 10);

  walls_.push_back(new Surface(170, 0, 330, 100, renderer_, WALL));
  walls_.push_back(new Surface(0, 100, 100, 380, renderer_, WALL));
  walls_.push_back(new Surface(0, 460, 500, 20, renderer_, WALL));
  walls_.push_back(new Surface(480, 0, 20, 480, renderer_, WALL));

  slick_floors_.push_back(new Surface(0, 100, 500, 380, renderer_, SLICK_FLOOR));

  walkable_floors_.push_back(new Surface(0, 0, screen_width_, screen_height_, renderer_, NORMAL_FLOOR));
  walkable_floors_.push_back(new Surface(50, 10, 50, 50, renderer_, NORMAL_FLOOR));
}

void GameScene::RunPostLoop() {
  delete player_;
  player_ = nullptr;

  while (!walls_.empty()) {
    Surface *wall = walls_.back();
    delete wall;
    walls_.pop_back();
  }

  while (!walkable_floors_.empty()) {
    Surface *wall = walkable_floors_.back();
    delete wall;
    walkable_floors_.pop_back();
  }

  while (!slick_floors_.empty()) {
    Surface *wall = slick_floors_.back();
    delete wall;
    slick_floors_.pop_back();
  }
}

void GameScene::RunSingleIterationEventHandler(SDL_Event &event) {

  Scene::RunSingleIterationEventHandler(event);
  player_->HandleEvent(event);

}

void GameScene::RunSingleIterationLoopBody() {

  if (player_->IsCollision(walls_.begin(), walls_.end())) {
    printf("Hit wall\n");
  } else if (player_->IsCollision(slick_floors_.begin(), slick_floors_.end())) {
    player_->MoveCharacterSlide();
  } else {
    player_->MoveCharacterStraight();
  }

  SDL_SetRenderDrawColor(renderer_, background_color_.r, background_color_.g, background_color_.b, background_color_.a);
  SDL_RenderClear(renderer_);

  for (Surface *walkable_floor : walkable_floors_) walkable_floor->Render();
  for (Surface *slick_floor : slick_floors_) slick_floor->Render();
  for (Surface *wall : walls_) wall->Render();
  player_->Render();

  SDL_RenderPresent(renderer_);

}

}
