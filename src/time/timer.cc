#include <SDL2/SDL.h>
#include "time/timer.h"

namespace sliding_blocks {

Timer::Timer() : start_time_(0), is_running_(false) {}

void Timer::StartTimer() {
  is_running_ = true;
  start_time_ = SDL_GetTicks();
}

uint32_t Timer::GetElapsedMilliseconds() const {

  if (!is_running_) {
    return 0;
  }

  return SDL_GetTicks() - start_time_;

}

}
