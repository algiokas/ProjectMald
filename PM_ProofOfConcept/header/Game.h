#pragma once

#include <SDL2/SDL.h>
#include "WorldSpace.h"

//Initialize SDL and create a window
bool init_game(SDL_Window*& window, SDL_Renderer*& renderer, ImageRepo*& loader, JsonRepo*& json_repo, WorldSpace*& world);

void close(SDL_Window* window, WorldSpace* world);