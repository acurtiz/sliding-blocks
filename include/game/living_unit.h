#ifndef SLIDINGBLOCKS_INCLUDE_GAME_LIVING_UNIT_H_
#define SLIDINGBLOCKS_INCLUDE_GAME_LIVING_UNIT_H_

namespace sliding_blocks {

class LivingUnit {

 public:
  explicit LivingUnit(int lives);
  void SetLives(int lives);
  int GetLives();
  void DecrementLives();
  bool HasRemainingLives();

 private:
  int lives_;

};

}

#endif //SLIDINGBLOCKS_INCLUDE_GAME_LIVING_UNIT_H_
