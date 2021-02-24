#pragma once

#include <string>

#include <SDL2/SDL.h>

class AssetLoader
{	
	std::string base_dir;
	SDL_Renderer* renderer;

public:
	bool img_init_success;

	AssetLoader(SDL_Renderer* gRenderer, std::string asset_dir = "assets/");
	SDL_Texture* loadTexture(std::string relative_path);
	SDL_Surface* loadSurface(std::string relative_path);
};