#pragma once

#include <SDL2/SDL.h>

#include <vector>
#include <string>
#include <iostream>

#include "Geometry.h"
#include "repository/JsonRepo.h"
#include "repository/ImageRepo.h"

class Animation
{
	//base value in ms used to determine frame interval
	const int BASE_ANIMATION_INTERVAL = 500;

	std::string name;
	float cyclespeed;
	int curr_frame_idx = 0;
	cardinaldir cardinal = cardinaldir::NODIR;
	std::vector<SDL_Texture*> frames;

public:
	Animation(std::string name, float cyclespeed) :
		name(name), cyclespeed(cyclespeed) {}

	Animation(std::string name, float cyclespeed, cardinaldir dir) :
		name(name), cyclespeed(cyclespeed), cardinal(dir) {}

	//get interval in ms between animation frames
	float frame_interval();

	//advance to the next frame 
	void advance_frame();

	//get the current animation frame
	SDL_Texture* current_frame();

	static std::map<std::string, Animation> load_animations(std::vector<std::string> asset_subdirs, nlohmann::json animations_root, ImageRepo* image_repo);

	//Get the key for a particular animation direction
	static std::string get_key(std::string aname, cardinaldir dir);
};