#include "scene/scene.h"
#include "text/text.h"
#include "button/rectangular_button.h"

#ifndef SLIDINGBLOCKS_INCLUDE_SCENE_TITLE_SCENE_H_
#define SLIDINGBLOCKS_INCLUDE_SCENE_TITLE_SCENE_H_

namespace sliding_blocks {

class TitleScene : public Scene {

 public:
  TitleScene(SDL_Renderer *renderer, SDL_Window *window, bool &global_quit);
  ~TitleScene();
  void RunPreLoop() override;
  void RunPostLoop() override;
  void RunSingleIterationEventHandler(SDL_Event &event) override;
  void RunSingleIterationLoopBody() override;

 private:
  Text *title_;
  TTF_Font *title_font_;

  Text *start_button_label_;
  RectangularButton *start_button_;

  Text *quit_button_label_;
  RectangularButton *quit_button_;

};

}

#endif //SLIDINGBLOCKS_INCLUDE_SCENE_TITLE_SCENE_H_
