#include <string>
#include <SDL2/SDL.h>
#include "level_loader.h"

#ifndef SLIDINGBLOCKS_INCLUDE_LEVEL_LOADER_RAPID_JSON_LOADER_H_
#define SLIDINGBLOCKS_INCLUDE_LEVEL_LOADER_RAPID_JSON_LOADER_H_

namespace sliding_blocks {

class RapidJsonLoader : public LevelLoader {

 public:
  RapidJsonLoader(std::string file_name,
                  SDL_Renderer *renderer);

};

}

#endif //SLIDINGBLOCKS_INCLUDE_LEVEL_LOADER_RAPID_JSON_LOADER_H_
