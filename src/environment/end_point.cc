#include "environment/end_point.h"
#include "environment/surface.h"

namespace sliding_blocks {

EndPoint::EndPoint(int id,
                   int top_left_x,
                   int top_left_y,
                   int width,
                   int height,
                   SDL_Color color,
                   GameComponent &game_component)
    : Surface(top_left_x, top_left_y, width, height, color, game_component),
      id_(id),
      has_next_stage_(false),
      next_stage_file_path_(""),
      next_stage_start_point_id_(-1) {
  printf("Constructing endpoint without next stage\n");
}

EndPoint::EndPoint(int id,
                   int top_left_x,
                   int top_left_y,
                   int width,
                   int height,
                   SDL_Color color,
                   std::string next_stage_file_path,
                   int next_stage_start_point_id,
                   GameComponent &game_component)
    : Surface(top_left_x, top_left_y, width, height, color, game_component),
      id_(id),
      has_next_stage_(true),
      next_stage_file_path_(next_stage_file_path),
      next_stage_start_point_id_(next_stage_start_point_id) {
  printf("Constructing endpoint with next stage\n");
}

int EndPoint::GetId() const {
  return id_;
}

bool EndPoint::HasNextStage() const {
  return has_next_stage_;
}

std::string EndPoint::GetNextStageFilePath() const {
  return next_stage_file_path_;
}

int EndPoint::GetNextStageStartPointId() const {
  return next_stage_start_point_id_;
}

}
