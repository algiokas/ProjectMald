#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <vector>

#include "WorldSpace.h"
#include "Util.h"

class GameChar {
	std::string name;
	std::string asset_dir;
	location loc;
	rect hitbox;	
	std::vector<SDL_Surface*> sprites;
	SDL_Surface* window_surface;
	WorldSpace* world;

	void load_sprites();

	public:
		GameChar(std::string name, std::string asset_dir, location init_loc, rect hbox, WorldSpace* world);
		~GameChar();
		void move_to(float x, float y);
		void move_towards(int x, int y, float spd);
		void draw_character(SDL_Surface* dest);
};