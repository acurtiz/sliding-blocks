#include <fstream>
#include <sstream>
#include "scene/game_scene.h"
#include "player/player.h"
#include "environment/surface.h"
#include "level_loader/rapid_json_loader.h"

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

  RapidJsonLoader level_loader("assets/level/1.json", renderer_);

  walls_ = level_loader.GetWalls();
  walkable_floors_ = level_loader.GetWalkableFloors();
  slick_floors_ = level_loader.GetSlickFloors();

  player_ = new Player(renderer_, 10, 10, 10, 10);

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
