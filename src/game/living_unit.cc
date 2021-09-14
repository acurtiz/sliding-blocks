#include "game/living_unit.h"

namespace sliding_blocks {

LivingUnit::LivingUnit(int lives) {
  lives_ = lives;
}

void LivingUnit::SetLives(int lives) {
  lives_ = lives;
}

int LivingUnit::GetLives() {
  return lives_;
}

void LivingUnit::DecrementLives() {
  lives_ -= 1;
}

bool LivingUnit::HasRemainingLives() {
  return lives_ > 0;
}

}
