#pragma once

#include <SDL2/SDL.h>

struct animation
{
	float cyclespeed;
	int num_frames;
	SDL_Texture** frames;
};
