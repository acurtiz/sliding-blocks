#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <boost/format.hpp>
#include <fstream>
#include <sstream>
#include "scene/game_scene.h"
#include "player/player.h"
#include "environment/surface.h"
#include "level_loader/json_file_loader.h"
#include "enemy/straight_moving_enemy.h"

namespace sliding_blocks {

GameScene::GameScene(SDL_Renderer *renderer,
                     SDL_Window *window,
                     bool &global_quit)
    : Scene(renderer, window, global_quit),
      player_(nullptr),
      level_loader_(renderer),
      current_stage_start_point_id_(0),
      font_(nullptr),
      remaining_lives_text_(nullptr),
      current_stage_text_(nullptr),
      current_level_width_(-1),
      current_level_height_(-1),
      current_level_name_() {

  font_ = TTF_OpenFont("assets/font/OpenSans-Regular.ttf", 18);
  if (font_ == nullptr) {
    throw std::runtime_error(boost::str(boost::format("Failed to load font, error: %1%\n") % TTF_GetError()));
  }

}

GameScene::~GameScene() {

  TTF_CloseFont(font_);

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
  enemies_ = level_loader_.GetEnemies();

  for (auto &start_point : start_points_) {
    start_point_id_to_obj_[start_point->GetId()] = start_point;
  }

  for (auto &end_point : end_points_) {
    end_point_id_to_obj_[end_point->GetId()] = end_point;
  }

  current_level_height_ = level_loader_.GetLevelHeight();
  current_level_width_ = level_loader_.GetLevelWidth();
  current_level_name_ = level_loader_.GetLevelName();

  // Walls implicitly surround every level
  walls_.push_back(new Wall(-1,
                            0,
                            1,
                            level_loader_.GetLevelHeight(),
                            {0xFF, 0x00, 0x00, 0xFF},
                            renderer_)); // bordering left side
  walls_.push_back(new Wall(level_loader_.GetLevelWidth(),
                            0,
                            1,
                            level_loader_.GetLevelHeight(),
                            {0xFF, 0x00, 0x00, 0xFF},
                            renderer_)); // bordering right side
  walls_.push_back(new Wall(0,
                            -1,
                            level_loader_.GetLevelWidth(),
                            1,
                            {0xFF, 0x00, 0x00, 0xFF},
                            renderer_)); // bordering top
  walls_.push_back(new Wall(0,
                            level_loader_.GetLevelHeight(),
                            level_loader_.GetLevelWidth(),
                            1,
                            {0xFF, 0x00, 0x00, 0xFF},
                            renderer_)); // bordering bottom

}

void GameScene::RunPreLoop() {

  std::string initial_level = "multi_stage_level/1.json";

  FreeLevelState();
  LoadAndInitializeLevel(initial_level);

  player_ = new Player(renderer_, 10, 10,
                       start_point_id_to_obj_[current_stage_start_point_id_]->GetTopLeftX(),
                       start_point_id_to_obj_[current_stage_start_point_id_]->GetTopLeftY());

  UpdateRemainingLivesText();
  UpdateCurrentStageText(current_level_name_);

}

void GameScene::RunPostLoop() {

  delete remaining_lives_text_;
  delete current_stage_text_;
  delete player_;
  player_ = nullptr;

  FreeLevelState();

}

void GameScene::RunSingleIterationEventHandler(SDL_Event &event) {

  player_->HandleEvent(event);

}

void GameScene::UpdateRemainingLivesText() {

  delete remaining_lives_text_;
  remaining_lives_text_ = new Text(renderer_,
                                   font_,
                                   {0xFF, 0xFF, 0xFF, 0xFF},
                                   boost::str(boost::format("Lives: %1%") % player_->GetLives()));

  remaining_lives_text_->SetTopLeftPosition(10, 505);

}

void GameScene::UpdateCurrentStageText(std::string stage_name) {

  delete current_stage_text_;
  current_stage_text_ = new Text(renderer_,
                                 font_,
                                 {0xFF, 0xFF, 0xFF, 0xFF},
                                 boost::str(boost::format("Current Level: %1%") % current_level_name_));
  current_stage_text_->SetTopLeftPosition(GetScreenWidth() - current_stage_text_->GetWidth() - 10,
                                          remaining_lives_text_->GetTopLeftY());

}

void GameScene::UpdateStateIfPlayerCollision(uint32_t elapsed_millis_since_last_frame) {

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

      std::string next_stage_file_path = endpoint->GetNextStageFilePath();
      int next_stage_start_point_id = endpoint->GetNextStageStartPointId();

      printf("Loading next stage: %s\n", next_stage_file_path.c_str());
      LoadAndInitializeLevel(next_stage_file_path);
      UpdateCurrentStageText(next_stage_file_path);
      player_->ResetMovement();
      current_stage_start_point_id_ = next_stage_start_point_id;
      player_->SetTopLeftPosition(start_point_id_to_obj_[current_stage_start_point_id_]->GetTopLeftX(),
                                  start_point_id_to_obj_[current_stage_start_point_id_]->GetTopLeftY());

    } else {
      printf("Quitting because no next stage\n");
      QuitLocal();
    }

  } else if (player_->IsCollision(walls_)) {

    if (player_->HasRemainingLives()) {
      player_->DecrementLives();
      UpdateRemainingLivesText();
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

}

void GameScene::UpdateStateIfEnemyCollision() {

  for (Enemy *enemy : enemies_) {
    if (enemy->IsCollision(walls_)) {
      enemy->UpdateIfCollision(*enemy->GetCollidingObject<Wall *>(walls_));
    }

  }

}

void GameScene::RunSingleIterationLoopBody() {

  uint32_t elapsed_millis_since_last_frame = timer_.GetElapsedMilliseconds();
  timer_.StartTimer();

  UpdateStateIfPlayerCollision(elapsed_millis_since_last_frame);
  UpdateStateIfEnemyCollision();
  for (Enemy *enemy : enemies_) enemy->Move(elapsed_millis_since_last_frame);

  SDL_SetRenderDrawColor(renderer_,
                         background_color_.r,
                         background_color_.g,
                         background_color_.b,
                         background_color_.a);
  SDL_RenderClear(renderer_);

  for (Surface *walkable_floor : walkable_floors_) walkable_floor->Render();
  for (Surface *slick_floor : slick_floors_) slick_floor->Render();
  for (Surface *wall : walls_) wall->Render();
  for (StartPoint *start_point : start_points_) start_point->Render();
  for (EndPoint *end_point : end_points_) end_point->Render();
  for (Enemy *enemy : enemies_) enemy->Render();
  player_->Render();

  remaining_lives_text_->Render();
  current_stage_text_->Render();

  SDL_RenderPresent(renderer_);

}

}
