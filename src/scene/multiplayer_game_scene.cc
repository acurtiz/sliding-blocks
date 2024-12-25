#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <boost/format.hpp>
#include <fstream>
#include <sstream>
#include "scene/multiplayer_game_scene.h"
#include "scene/title_scene.h"
#include "player/player.h"
#include "environment/surface.h"
#include "level_loader/json_file_loader.h"
#include "enemy/straight_moving_enemy.h"
#include "network/client.h"
#include "message/player_position_message.h"
#include "message/initialize_player_message.h"

namespace sliding_blocks {

MultiplayerGameScene::MultiplayerGameScene(SceneExecutor &scene_executor,
                                           GameComponent &game_component,
                                           NetworkClient &network_client)
    : Scene(scene_executor, game_component),
      player_(nullptr),
      level_loader_(game_component),
      current_level_file_path_("multi_stage_level/1.json"),
      current_level_start_point_id_(0),
      font_(nullptr),
      remaining_lives_text_(nullptr),
      current_stage_text_(nullptr),
      current_level_width_(-1),
      current_level_height_(-1),
      current_level_name_(),
      death_menu_(nullptr),
      network_client_(network_client),
      run_game_(false),
      non_controlled_players_() {

  font_ = TTF_OpenFont("assets/font/OpenSans-Regular.ttf", 18);
  if (font_ == nullptr) {
    throw std::runtime_error(boost::str(boost::format("Failed to load font, error: %1%\n") % TTF_GetError()));
  }

  LoadAndInitializeLevelEnvironment(current_level_file_path_, current_level_start_point_id_);
  ResetPlayerLivesAndPosition();

  death_menu_ = new DeathMenu(game_component,
                              [this] {
                                death_menu_->Close();
                                scene_executor_.SwitchScene(typeid(TitleScene));
                              },
                              [this] {
                                death_menu_->Close();
                                LoadAndInitializeLevelEnvironment(current_level_file_path_,
                                                                  current_level_start_point_id_);
                                ResetPlayerLivesAndPosition();
                              }
  );

  win_menu_ = new WinMenu(game_component,
                          [this] {
                            win_menu_->Close();
                            scene_executor_.SwitchScene(typeid(TitleScene));
                          });
}

MultiplayerGameScene::~MultiplayerGameScene() {

  delete remaining_lives_text_;
  delete current_stage_text_;
  delete player_;
  delete death_menu_;
  delete win_menu_;

  FreeLevelState();

  TTF_CloseFont(font_);

}

void MultiplayerGameScene::RunSingleIterationEventHandler(SDL_Event &event) {

  player_->HandleEvent(event);
  death_menu_->RunSingleIterationEventHandler(event);
  win_menu_->RunSingleIterationEventHandler(event);
}

void MultiplayerGameScene::RunSingleIterationLoopBody() {

  network_client_.CheckHostService();

  network_client_.SendData(sliding_blocks_networking::PlayerPositionMessage(player_->GetTopLeftX(),
                                                                            player_->GetTopLeftY()).Serialize());

  if (!run_game_) {
    network_client_.SendData("GAME_LOADED");
    return;
  }

  uint32_t elapsed_millis_since_last_frame = timer_.GetElapsedMilliseconds();
  timer_.StartTimer();

  if (!death_menu_->IsOpened() && !win_menu_->IsOpened()) {
    GetCamera()->CenterOnObject(*player_);
    UpdatePlayerStateAndHandleCollisions(elapsed_millis_since_last_frame);
    UpdateEnemyStateAndHandleCollision(elapsed_millis_since_last_frame);
  }

  SDL_SetRenderDrawColor(GetRenderer(),
                         background_color_.r,
                         background_color_.g,
                         background_color_.b,
                         background_color_.a);
  SDL_RenderClear(GetRenderer());

  for (Surface *walkable_floor: walkable_floors_) walkable_floor->Render();
  for (Surface *slick_floor: slick_floors_) slick_floor->Render();
  for (Surface *wall: walls_) wall->Render();
  for (StartPoint *start_point: start_points_) start_point->Render();
  for (EndPoint *end_point: end_points_) end_point->Render();
  for (Enemy *enemy: enemies_) enemy->Render();
  for (auto kv: non_controlled_players_) kv.second->Render();
  player_->Render();

  remaining_lives_text_->Render();
  current_stage_text_->Render();

  death_menu_->RunSingleIterationLoopBody();
  win_menu_->RunSingleIterationLoopBody();

  SDL_RenderPresent(GetRenderer());

}

void MultiplayerGameScene::HandleReceivedData(const std::string &data) {

  printf("HandleReceivedData [%s]\n", data.c_str());

  auto *message = sliding_blocks_networking::NetworkMessage::DeserializeAny(data);

  auto *initialize_player_message = dynamic_cast<const sliding_blocks_networking::InitializePlayerMessage *>(message);
  if (initialize_player_message != nullptr) {
    non_controlled_players_.erase(initialize_player_message->GetClientId());
    non_controlled_players_[initialize_player_message->GetClientId()] =
        new NonControlledPlayer(*this, 10, 10, initialize_player_message->GetX(), initialize_player_message->GetY());
  }

  if (non_controlled_players_.empty()) {
    printf("Waiting on player initialization message\n");
    return;
  }

  if (!run_game_ && data == "START_COUNTDOWN") {
    run_game_ = true;
    return;
  }

  auto *player_position_message = dynamic_cast<const sliding_blocks_networking::PlayerPositionMessage *>(message);
  if (player_position_message != nullptr) {
    non_controlled_players_[player_position_message->GetClientId()]->SetTopLeftPosition(player_position_message->GetX(),
                                                                                        player_position_message->GetY());
  }

}

void MultiplayerGameScene::PreSwitchHook() {
  current_level_file_path_ = "multi_stage_level/1.json";
  current_level_start_point_id_ = 0;
  LoadAndInitializeLevelEnvironment(current_level_file_path_, current_level_start_point_id_);
  ResetPlayerLivesAndPosition();

  network_client_.RegisterHandler(*this);

}

void MultiplayerGameScene::PostSwitchHook() {

  death_menu_->Close();
  win_menu_->Close();

  network_client_.DeregisterHandler();
}

void MultiplayerGameScene::ResetPlayerPosition() {
  player_->SetTopLeftPosition(start_point_id_to_obj_[current_level_start_point_id_]->GetTopLeftX(),
                              start_point_id_to_obj_[current_level_start_point_id_]->GetTopLeftY());
  player_->ResetMovement();
}

void MultiplayerGameScene::ResetPlayerLivesAndPosition() {

  delete player_;
  player_ = new Player(*this, 10, 10,
                       start_point_id_to_obj_[current_level_start_point_id_]->GetTopLeftX(),
                       start_point_id_to_obj_[current_level_start_point_id_]->GetTopLeftY());
  SetPlayerLives(player_->GetLives());

}

void MultiplayerGameScene::FreeLevelState() {

  level_loader_.FreeAll();
  start_point_id_to_obj_.clear();
  end_point_id_to_obj_.clear();
  non_controlled_players_.clear();

}

void MultiplayerGameScene::LoadAndInitializeLevelEnvironment(const std::string &level_file_path, int start_point_id) {

  FreeLevelState();

  level_loader_.Load("assets/level/" + level_file_path);

  walls_ = level_loader_.GetWalls();
  walkable_floors_ = level_loader_.GetWalkableFloors();
  slick_floors_ = level_loader_.GetSlickFloors();
  start_points_ = level_loader_.GetStartPoints();
  end_points_ = level_loader_.GetEndPoints();
  enemies_ = level_loader_.GetEnemies();

  for (auto &start_point: start_points_) {
    start_point_id_to_obj_[start_point->GetId()] = start_point;
  }

  for (auto &end_point: end_points_) {
    end_point_id_to_obj_[end_point->GetId()] = end_point;
  }

  current_level_height_ = level_loader_.GetLevelHeight();
  current_level_width_ = level_loader_.GetLevelWidth();
  current_level_name_ = level_loader_.GetLevelName();

  delete current_stage_text_;
  current_stage_text_ = new Text(GetRenderer(),
                                 font_,
                                 {0xFF, 0xFF, 0xFF, 0x00},
                                 boost::str(boost::format("Current Level: %1%") % current_level_name_));
  current_stage_text_->SetTopLeftPosition(GetScreenWidth() - current_stage_text_->GetWidth() - 10,
                                          GetScreenHeight() - current_stage_text_->GetHeight() - 10);

  GetCamera()->SetBoundaries(0, current_level_width_, current_level_height_, 0);

  current_level_start_point_id_ = start_point_id;

}

void MultiplayerGameScene::SetPlayerLives(int lives_remaining) {

  player_->SetLives(lives_remaining);
  delete remaining_lives_text_;
  remaining_lives_text_ = new Text(GetRenderer(),
                                   font_,
                                   {0xFF, 0xFF, 0xFF, 0x00},
                                   boost::str(boost::format("Lives: %1%") % player_->GetLives()));
  remaining_lives_text_->SetTopLeftPosition(10, GetScreenHeight() - remaining_lives_text_->GetHeight() - 10);

}

void MultiplayerGameScene::UpdatePlayerStateAndHandleCollisions(uint32_t elapsed_millis_since_last_frame) {

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
      current_level_file_path_ = endpoint->GetNextStageFilePath();
      LoadAndInitializeLevelEnvironment(endpoint->GetNextStageFilePath(), endpoint->GetNextStageStartPointId());
      ResetPlayerPosition();
    } else {
      win_menu_->Open();
    }

  } else if (player_->IsCollision(walls_) || player_->IsCollision(enemies_)) {

    if (player_->HasRemainingLives()) {

      SetPlayerLives(player_->GetLives() - 1);

      // TODO: for now, the only way to reset enemies is to reload the entire level. We can optimize this later
      LoadAndInitializeLevelEnvironment(current_level_file_path_, current_level_start_point_id_);
      ResetPlayerPosition();

    } else {
      death_menu_->Open();
      printf("Player died but no remaining lives; exiting!\n");
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

void MultiplayerGameScene::UpdateEnemyStateAndHandleCollision(uint32_t elapsed_millis_since_last_frame) {

  for (Enemy *enemy: enemies_) {

    enemy->Move(elapsed_millis_since_last_frame);

    if (enemy->IsCollision(walls_)) {
      enemy->UpdateIfCollision(*enemy->GetCollidingObject<Wall *>(walls_));
    }

  }

}

}
