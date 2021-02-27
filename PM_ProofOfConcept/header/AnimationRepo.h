#pragma once

#include <SDL2/SDL.h>

#include <vector>
#include <string>
#include <iostream>

#include "JsonRepo.h"
#include "ImageRepo.h"

class Animation
{
	//base value in ms used to determine frame interval
	const int BASE_ANIMATION_INTERVAL = 500;

	std::string name;
	float cyclespeed;
	int curr_frame_idx;
	std::vector<SDL_Texture*> frames;

public:
	Animation(std::string name, float cyclespeed) :
		name(name), cyclespeed(cyclespeed), curr_frame_idx(0) {}

	//get interval in ms between animation frames
	float frame_interval();

	//advance to the next frame 
	void advance_frame();

	//get the current animation frame
	SDL_Texture* get_current_frame();


	//Load animations from a 
	static std::vector<Animation> load_animations(std::vector<std::string> asset_subdirs, rapidjson::Value* animations_root, ImageRepo* image_repo);
};