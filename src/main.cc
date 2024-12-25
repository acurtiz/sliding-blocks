// Necessary to build on Windows.
#define SDL_MAIN_HANDLED

#include "game/game.h"

int main() {

  sliding_blocks::Game game = sliding_blocks::Game();
  game.Run();
  return 0;

}
