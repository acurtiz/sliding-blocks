#include <fstream>
#include <sstream>
#include "scene/game_scene.h"
#include "player/player.h"
#include "environment/surface.h"
#include "level_loader/json_file_loader.h"

namespace sliding_blocks {

GameScene::GameScene(SDL_Renderer *renderer,
                     SDL_Window *window,
                     bool &global_quit,
                     int screen_height,
                     int screen_width)
    : Scene(renderer, window, global_quit),
      screen_height_(screen_width),
      screen_width_(screen_width),
      player_(nullptr),
      level_loader_(renderer),
      start_point_id_(0) {

}

void GameScene::RunPreLoop() {

  level_loader_.Load("assets/level/1.json");

  walls_ = level_loader_.GetWalls();
  walkable_floors_ = level_loader_.GetWalkableFloors();
  slick_floors_ = level_loader_.GetSlickFloors();
  start_points_ = level_loader_.GetStartPoints();
  end_points_ = level_loader_.GetEndPoints();

  for (auto &start_point : start_points_) {
    start_point_id_to_obj_[start_point->GetId()] = start_point;
  }

  for (auto &end_point : end_points_) {
    end_point_id_to_obj_[end_point->GetId()] = end_point;
  }

  player_ = new Player(renderer_, 10, 10,
                       start_point_id_to_obj_[start_point_id_]->GetTopLeftX(),
                       start_point_id_to_obj_[start_point_id_]->GetTopLeftY());

}

void GameScene::RunPostLoop() {

  delete player_;
  player_ = nullptr;

  level_loader_.FreeAll();

}

void GameScene::RunSingleIterationEventHandler(SDL_Event &event) {

  Scene::RunSingleIterationEventHandler(event);
  player_->HandleEvent(event);

}

void GameScene::RunSingleIterationLoopBody() {

  if (player_->IsCollision(start_points_)) {
    player_->MoveCharacterStraight();
  } else if (player_->IsCollision(end_points_)) {
    // TODO need to be able to figure out which object this was
    printf("Reached end point - should load next level!\n");
  } else if (player_->IsCollision(walls_)) {
    printf("Hit wall, so not moving anymore.\n");
  } else if (player_->IsCollision(slick_floors_)) {
    player_->MoveCharacterSlide();
  } else {
    player_->MoveCharacterStraight();
  }

  SDL_SetRenderDrawColor(renderer_, background_color_.r, background_color_.g, background_color_.b, background_color_.a);
  SDL_RenderClear(renderer_);

  for (Surface *walkable_floor : walkable_floors_) walkable_floor->Render();
  for (Surface *slick_floor : slick_floors_) slick_floor->Render();
  for (Surface *wall : walls_) wall->Render();
  for (const auto &entry : start_point_id_to_obj_) entry.second->Render();
  for (const auto &entry : end_point_id_to_obj_) entry.second->Render();
  player_->Render();

  SDL_RenderPresent(renderer_);

}

}
