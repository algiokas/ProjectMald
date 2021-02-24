#pragma once

#include <SDL2/SDL.h>
#include "WorldSpace.h"

//Initialize SDL and create a window
bool init_game(SDL_Window*& window, SDL_Renderer*& renderer, ImageRepo*& loader, std::string asset_dir, WorldSpace*& world, int window_width, int window_height);

bool load_image(SDL_Surface*& imgSurface, const char* filepath);

void close(SDL_Window* window, WorldSpace* world);