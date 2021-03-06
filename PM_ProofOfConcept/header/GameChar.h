#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <vector>

#include "WorldSpace.h"
#include "Geometry.h"
#include "repository/ImageRepo.h"
#include "repository/JsonRepo.h"
#include "Animation.h"

class WorldSpace;

class GameChar {
	std::string name;

	//Character type members
	int type_id;
	std::string type_name;

	//Location, movement, and collision
	vec2d loc;
	vec2d dest;
	vec2d velocity;
	float max_speed;
	vec2d centroid;
	rect hitbox;
	cardinaldir cardinal;
	Uint32 movement_timer;

	//rendering data
	Uint32 animation_timer;
	SDL_Texture* static_sprite = NULL;
	std::map<std::string, Animation> animations;
	std::string current_anim = "";
	
	WorldSpace* world;

	//Private constructor, class should be instantiated using CreateCharacter
	GameChar(std::string name, int type_id, vec2d init_loc, float max_speed, WorldSpace* world);

	//Load static sprite and animation sprites
	void load_sprites(ImageRepo* img_repo, std::string template_name, rapidjson::Value* char_template);
	SDL_Texture* current_sprite();

	//Advance the currently playing animation to the next frame
	void advance_animation();

	//Checks the list of animations for an animation named [aname]
	//if found, sets it as the current animation. If not found, stops animation.
	void play_animation(std::string aname);

	//Move in the direction of the point d
	void move_towards(vec2d d);

public:
	
	static GameChar* CreateCharacter(std::string name, int id, vec2d init_loc, WorldSpace* world, JsonRepo* json_repo, ImageRepo* img_repo);

	//Set a destination that the character will move towards
	void set_destination(vec2d d);
	
	//Update the character 
	void update(float speedmult);

	//Draw the character's current sprite state using the provided rend
	void render(SDL_Renderer* renderer);
};