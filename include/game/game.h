#ifndef SLINDINGBLOCKS_INCLUDE_GAME_GAME_H_
#define SLINDINGBLOCKS_INCLUDE_GAME_GAME_H_

#include <typeindex>
#include <map>
#include <SDL2/SDL.h>
#include "scene/scene.h"

namespace sliding_blocks {

class Game {

 public:
  Game();
  ~Game();
  void Run();
  void SwitchScene(std::type_index scene_type);
  void Quit();

  SDL_Renderer *GetRenderer() const;
  int GetScreenWidth() const;
  int GetScreenHeight() const;

 private:
  void LoadScenes();
  void UnloadScenes();
  std::map<std::type_index, Scene *> type_to_scene_map_;
  Scene *scene_current_;
  Scene *scene_next_;
  const int screen_width_ = 500;
  const int screen_height_ = 540;
  SDL_Window *window_ = nullptr;
  SDL_Renderer *renderer_ = nullptr;
  bool global_quit_ = false;

};

}
#endif //SLINDINGBLOCKS_INCLUDE_GAME_GAME_H_
