#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <vector>

#include "WorldSpace.h"
#include "Geometry.h"
#include "ImageRepo.h"
#include "JsonRepo.h"

class WorldSpace;

class GameChar {
	std::string name;
	int type_id;
	vec2d loc;
	vec2d dest;
	vec2d centroid;
	rect hitbox;
	SDL_Texture* static_sprite;
	std::vector<SDL_Texture*> sprites;
	WorldSpace* world;

	void load_sprites();
	GameChar(std::string name, int type_id, vec2d init_loc, WorldSpace* world) :
		name(name), type_id(type_id), loc(init_loc), world(world) {}

public:
	
	~GameChar();
	static GameChar* CreateCharacter(std::string name, int id, vec2d init_loc, WorldSpace* world, JsonRepo* json_repo, ImageRepo* img_repo);
	void move_to(vec2d d);
	void move_towards(vec2d d, float spd);
	void set_destination(vec2d d);
	void update();
	void render(SDL_Renderer* renderer);
};