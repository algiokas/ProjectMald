#pragma once

#include <string>
#include <map>

#include <SDL2/SDL.h>

class ImageRepo
{	
	std::string base_dir;
	SDL_Renderer* renderer;
	std::map<std::string, SDL_Texture*> image_cache;

	void flush_cache();
public:
	bool img_init_success;

	ImageRepo(SDL_Renderer* gRenderer, std::string asset_dir = "assets/");
	~ImageRepo();
	SDL_Texture* loadTexture(std::string relative_path);
	SDL_Surface* loadSurface(std::string relative_path);
};