#pragma once

#include <SDL2/SDL.h>

#include <map>
#include <string>

class Animation
{
	float cyclespeed;
	int num_frames;
	SDL_Texture* frames[];
};

class AnimationRepo
{
	std::map<std::string, Animation*> animation_cache;
};