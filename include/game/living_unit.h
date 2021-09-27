#ifndef SLIDINGBLOCKS_INCLUDE_GAME_LIVING_UNIT_H_
#define SLIDINGBLOCKS_INCLUDE_GAME_LIVING_UNIT_H_

namespace sliding_blocks {

class LivingUnit {

 public:
  explicit LivingUnit(int lives);
  void SetLives(int lives);
  int GetLives() const;
  void DecrementLives();
  bool HasRemainingLives() const;
  void ResetLives();

 private:
  int remaining_lives_;
  const int starting_lives_;

};

}

#endif //SLIDINGBLOCKS_INCLUDE_GAME_LIVING_UNIT_H_
