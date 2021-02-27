#pragma once

#include <string>
#include <map>
#include <vector>

#include <SDL2/SDL.h>

#include "Global.h"

class ImageRepo
{	
	const std::string PNG_EXTENSION = ".png";

	SDL_Renderer* renderer;
	std::map<std::string, SDL_Texture*> image_cache;

	void flush_cache();
	SDL_Surface* loadSurface(std::string relative_path);

public:
	bool img_init_success;

	ImageRepo(SDL_Renderer* gRenderer);
	~ImageRepo();
	SDL_Texture* loadTexture(std::string relative_path);
	SDL_Texture* loadTexture(std::string asset_subdir, std::string fname);
	SDL_Texture* loadTexture(std::vector<std::string> asset_subdirs, std::string fname);
	
};