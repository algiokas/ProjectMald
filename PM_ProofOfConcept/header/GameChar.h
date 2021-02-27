#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <vector>

#include "WorldSpace.h"
#include "Geometry.h"
#include "ImageRepo.h"
#include "JsonRepo.h"
#include "AnimationRepo.h"

class WorldSpace;

class GameChar {
	std::string name;

	//Character type members
	int type_id;
	std::string type_name;

	//Location and geometry
	vec2d loc;
	vec2d dest;
	vec2d centroid;
	rect hitbox;

	//rendering data
	SDL_Texture* static_sprite;
	Animation* current_animation;
	std::vector<Animation> sprites;
	
	WorldSpace* world;

	void load_sprites(ImageRepo* img_repo, rapidjson::Value char_template);
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