#ifndef SLIDINGBLOCKS_INCLUDE_TIME_TIMER_H_
#define SLIDINGBLOCKS_INCLUDE_TIME_TIMER_H_

namespace sliding_blocks {

class Timer {
 public:
  Timer();
  void StartTimer();
  uint32_t GetElapsedMilliseconds() const;

 private:
  bool is_running_;
  uint32_t start_time_;

};

}

#endif //SLIDINGBLOCKS_INCLUDE_TIME_TIMER_H_
