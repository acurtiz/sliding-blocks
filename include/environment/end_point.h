#include <string>
#include "environment/surface.h"

#ifndef SLIDINGBLOCKS_INCLUDE_ENVIRONMENT_END_POINT_H_
#define SLIDINGBLOCKS_INCLUDE_ENVIRONMENT_END_POINT_H_

namespace sliding_blocks {

class EndPoint : public Surface {

 public:
  EndPoint(int id,
           int top_left_x,
           int top_left_y,
           int width,
           int height,
           SDL_Renderer *renderer);

  EndPoint(int id,
           int top_left_x,
           int top_left_y,
           int width,
           int height,
           std::string next_stage_file_path,
           int next_stage_start_point_id,
           SDL_Renderer *renderer);

  int GetId() const;
  bool HasNextStage() const;
  std::string GetNextStageFilePath() const;
  int GetNextStageStartPointId() const;

 private:
  int id_;
  bool has_next_stage_;
  int next_stage_start_point_id_;
  std::string next_stage_file_path_;

};

}

#endif //SLIDINGBLOCKS_INCLUDE_ENVIRONMENT_END_POINT_H_
