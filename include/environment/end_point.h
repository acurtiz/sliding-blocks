#ifndef SLIDINGBLOCKS_INCLUDE_ENVIRONMENT_END_POINT_H_
#define SLIDINGBLOCKS_INCLUDE_ENVIRONMENT_END_POINT_H_

#include <string>
#include "environment/surface.h"
#include "game/game_component.h"

namespace sliding_blocks {

class EndPoint : public Surface {

 public:
  EndPoint(int id,
           int top_left_x,
           int top_left_y,
           int width,
           int height,
           GameComponent &game_component);

  EndPoint(int id,
           int top_left_x,
           int top_left_y,
           int width,
           int height,
           std::string next_stage_file_path,
           int next_stage_start_point_id,
           GameComponent &game_component);

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
