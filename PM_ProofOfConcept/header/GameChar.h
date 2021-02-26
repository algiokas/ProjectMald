#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <vector>

#include "WorldSpace.h"
#include "Geometry.h"
#include "ImageRepo.h"

class WorldSpace;

class GameChar {
	std::string name;
	std::string asset_dir;
	vec2d loc;
	vec2d dest;
	vec2d centroid;
	rect hitbox;
	SDL_Surface* window_surface;
	std::vector<SDL_Texture*> sprites;
	WorldSpace* world;
	ImageRepo* image_repo;

	void load_sprites();

public:
	GameChar(std::string name, std::string asset_dir, vec2d init_loc, WorldSpace* world, ImageRepo* loader);
	~GameChar();
	void move_to(vec2d d);
	void move_towards(vec2d d, float spd);
	void set_destination(vec2d d);
	void update();
	void render(SDL_Renderer* renderer);
};