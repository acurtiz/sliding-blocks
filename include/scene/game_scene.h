#include <vector>
#include <map>
#include "scene/scene.h"
#include "player/player.h"
#include "environment/surface.h"
#include "environment/start_point.h"
#include "environment/end_point.h"
#include "level_loader/json_file_loader.h"

#ifndef SLIDINGBLOCKS_INCLUDE_SCENE_GAME_SCENE_H_
#define SLIDINGBLOCKS_INCLUDE_SCENE_GAME_SCENE_H_

namespace sliding_blocks {

class GameScene : public Scene {

 public:
  GameScene(SDL_Renderer *renderer, SDL_Window *window, bool &global_quit, int screen_height, int screen_width);
  void RunPreLoop() override;
  void RunPostLoop() override;
  void RunSingleIterationEventHandler(SDL_Event &event) override;
  void RunSingleIterationLoopBody() override;

 private:

  void FreeLevelState();
  void LoadAndInitializeLevel(const std::string &level_file_path);

  SDL_Color background_color_ = {0x00, 0x00, 0x00, 0xFF};
  int screen_height_;
  int screen_width_;
  Player *player_;
  std::vector<Surface *> walls_;
  std::vector<Surface *> slick_floors_;
  std::vector<Surface *> walkable_floors_;
  std::vector<StartPoint *> start_points_;
  std::vector<EndPoint *> end_points_;
  std::map<int, StartPoint *> start_point_id_to_obj_;
  std::map<int, EndPoint *> end_point_id_to_obj_;

  JsonFileLoader level_loader_;

};

}

#endif //SLIDINGBLOCKS_INCLUDE_SCENE_GAME_SCENE_H_
