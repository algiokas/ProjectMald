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
	point2d loc;
	point2d dest;
	point2d centroid;
	rect hitbox;
	SDL_Surface* window_surface;
	std::vector<SDL_Texture*> sprites;
	WorldSpace* world;
	ImageRepo* loader;

	void load_sprites();
	point2d centroid();

public:
	GameChar(std::string name, std::string asset_dir, point2d init_loc, WorldSpace* world, ImageRepo* loader);
	~GameChar();
	void move_to(float x, float y);
	void move_towards(float x, float y, float spd);
	void set_destination(point2d d);
	void update();
	void render(SDL_Renderer* renderer);
};