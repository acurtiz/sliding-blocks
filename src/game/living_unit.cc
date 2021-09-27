#include "game/living_unit.h"

namespace sliding_blocks {

LivingUnit::LivingUnit(int lives)
    : starting_lives_(lives), remaining_lives_(lives) {}

void LivingUnit::SetLives(int lives) {
  remaining_lives_ = lives;
}

int LivingUnit::GetLives() const {
  return remaining_lives_;
}

void LivingUnit::DecrementLives() {
  remaining_lives_ -= 1;
}

bool LivingUnit::HasRemainingLives() const {
  return remaining_lives_ > 0;
}

void LivingUnit::ResetLives() {
  remaining_lives_ = starting_lives_;
}

}
