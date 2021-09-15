#include <vector>
#include <map>
#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>
#include "scene/scene.h"
#include "player/player.h"
#include "environment/surface.h"
#include "environment/start_point.h"
#include "environment/end_point.h"
#include "level_loader/json_file_loader.h"
#include "time/timer.h"
#include "text/text.h"

#ifndef SLIDINGBLOCKS_INCLUDE_SCENE_GAME_SCENE_H_
#define SLIDINGBLOCKS_INCLUDE_SCENE_GAME_SCENE_H_

namespace sliding_blocks {

class GameScene : public Scene {

 public:
  GameScene(SDL_Renderer *renderer, SDL_Window *window, bool &global_quit);
  ~GameScene();

 private:
  void RunPreLoop() override;
  void RunPostLoop() override;
  void RunSingleIterationEventHandler(SDL_Event &event) override;
  void RunSingleIterationLoopBody() override;
  void FreeLevelState();
  void LoadAndInitializeLevel(const std::string &level_file_path);
  void UpdateRemainingLivesText();
  void UpdateCurrentStageText(std::string stage_name);
  void UpdateStateIfPlayerCollision(uint32_t elapsed_millis_since_last_frame);

  SDL_Color background_color_ = {0x00, 0x00, 0x00, 0xFF}; // black
  Player *player_;
  std::vector<Surface *> walls_;
  std::vector<Surface *> slick_floors_;
  std::vector<Surface *> walkable_floors_;
  std::vector<StartPoint *> start_points_;
  std::vector<EndPoint *> end_points_;
  std::map<int, StartPoint *> start_point_id_to_obj_;
  std::map<int, EndPoint *> end_point_id_to_obj_;
  std::string current_level_name_;
  int current_level_width_;
  int current_level_height_;

  int current_stage_start_point_id_;

  JsonFileLoader level_loader_;

  Timer timer_;

  TTF_Font *font_;
  Text *remaining_lives_text_;
  Text *current_stage_text_;

};

}

#endif //SLIDINGBLOCKS_INCLUDE_SCENE_GAME_SCENE_H_
