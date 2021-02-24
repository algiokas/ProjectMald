#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <vector>

#include "WorldSpace.h"
#include "Util.h"
#include "ImageRepo.h"

class WorldSpace;

class GameChar {
	std::string name;
	std::string asset_dir;
	location loc;
	rect hitbox;
	SDL_Surface* window_surface;
	std::vector<SDL_Texture*> sprites;
	WorldSpace* world;
	ImageRepo* loader;

	void load_sprites();

public:
	GameChar(std::string name, std::string asset_dir, location init_loc, WorldSpace* world, ImageRepo* loader);
	~GameChar();
	void move_to(float x, float y);
	void move_towards(int x, int y, float spd);
	void draw_character(SDL_Renderer* renderer);
};