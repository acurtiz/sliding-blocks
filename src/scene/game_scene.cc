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
      current_stage_start_point_id_(0) {

}

void GameScene::FreeLevelState() {

  level_loader_.FreeAll();
  start_point_id_to_obj_.clear();
  end_point_id_to_obj_.clear();

}

void GameScene::LoadAndInitializeLevel(const std::string &level_file_path) {

  FreeLevelState();

  level_loader_.Load("assets/level/" + level_file_path);

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

}

void GameScene::RunPreLoop() {

  FreeLevelState();
  LoadAndInitializeLevel("multi_stage_level/1.json");

  player_ = new Player(renderer_, 10, 10,
                       start_point_id_to_obj_[current_stage_start_point_id_]->GetTopLeftX(),
                       start_point_id_to_obj_[current_stage_start_point_id_]->GetTopLeftY());

}

void GameScene::RunPostLoop() {

  delete player_;
  player_ = nullptr;

  FreeLevelState();

}

void GameScene::RunSingleIterationEventHandler(SDL_Event &event) {

  Scene::RunSingleIterationEventHandler(event);
  player_->HandleEvent(event);

}

void GameScene::RunSingleIterationLoopBody() {

  uint32_t elapsed_millis_since_last_frame = timer_.GetElapsedMilliseconds();
  timer_.StartTimer();

  if (player_->IsCollision(start_points_)) {

    // If player was sliding but just landed on non-slick land, they should stop moving (as opposed to
    // moving to the last clicked destination)
    if (player_->IsSliding()) {
      player_->ResetMovement();
    } else {
      player_->MoveCharacterStraight(elapsed_millis_since_last_frame);
    }

  } else if (player_->IsCollision(end_points_)) {

    auto endpoint = player_->GetCollidingObject<EndPoint *>(end_points_);

    if (endpoint->HasNextStage()) {

      printf("Loading next stage: %s\n", endpoint->GetNextStageFilePath().c_str());
      LoadAndInitializeLevel(endpoint->GetNextStageFilePath());
      player_->ResetMovement();
      current_stage_start_point_id_ = endpoint->GetNextStageStartPointId();
      player_->SetTopLeftPosition(start_point_id_to_obj_[current_stage_start_point_id_]->GetTopLeftX(),
                                  start_point_id_to_obj_[current_stage_start_point_id_]->GetTopLeftY());

    } else {
      printf("Quitting because no next stage\n");
      QuitLocal();
    }

  } else if (player_->IsCollision(walls_)) {

    if (player_->HasRemainingLives()) {
      player_->DecrementLives();
      player_->SetTopLeftPosition(start_point_id_to_obj_[current_stage_start_point_id_]->GetTopLeftX(),
                                  start_point_id_to_obj_[current_stage_start_point_id_]->GetTopLeftY());
      printf("Player hit wall thus lost a life! Remaining lives: %d\n", player_->GetLives());
    } else {
      printf("Player died but no remaining lives; exiting!\n");
      QuitLocal();
    }

  } else if (player_->IsCollision(slick_floors_)) {

    player_->MoveCharacterSlide(elapsed_millis_since_last_frame);

  } else {

    if (player_->IsSliding()) {
      player_->ResetMovement();
    } else {
      player_->MoveCharacterStraight(elapsed_millis_since_last_frame);
    }

  }

  SDL_SetRenderDrawColor(renderer_, background_color_.r, background_color_.g, background_color_.b, background_color_.a);
  SDL_RenderClear(renderer_);

  for (Surface *walkable_floor : walkable_floors_) walkable_floor->Render();
  for (Surface *slick_floor : slick_floors_) slick_floor->Render();
  for (Surface *wall : walls_) wall->Render();
  for (StartPoint *start_point : start_points_) start_point->Render();
  for (EndPoint *end_point : end_points_) end_point->Render();
  player_->Render();

  SDL_RenderPresent(renderer_);

}

}
