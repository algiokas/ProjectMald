#include "../header/ImageRepo.h"

#include <SDL2/SDL_image.h>

#include <iostream>


ImageRepo::ImageRepo(SDL_Renderer* gRenderer, std::string asset_dir)
{
    this->base_dir = asset_dir;
    this->renderer = gRenderer;
    this->img_init_success = false;

    int imgFlags = IMG_INIT_PNG;
    this->img_init_success = IMG_Init(imgFlags) & imgFlags; //Bitwise AND
    if (!img_init_success)
    {
        std::cerr << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
    }
}

ImageRepo::~ImageRepo()
{
    std::map<std::string, SDL_Texture*>::iterator it;
    for (it = image_cache.begin(); it != image_cache.end(); it++)
    {
        SDL_DestroyTexture(it->second);
    }
    image_cache.clear();
}

SDL_Texture* ImageRepo::loadTexture(std::string relative_path)
{
    auto it = image_cache.find(relative_path);
    if (it == image_cache.end())
    {
        SDL_Texture* tex = NULL;
        SDL_Surface* loaded_surface = this->loadSurface(relative_path);
        if (loaded_surface != NULL) {
            tex = SDL_CreateTextureFromSurface(this->renderer, loaded_surface);
            if (tex == NULL)
            {
                std::cerr << "Unable to create texture from " << base_dir + relative_path << " ! SDL Error: " << SDL_GetError() << std::endl;
            }
            SDL_FreeSurface(loaded_surface);
        }
        it = image_cache.insert(it, std::make_pair(relative_path, tex));
    }
    return it->second;
}


SDL_Surface* ImageRepo::loadSurface(std::string relative_path)
{
    std::string full_path = base_dir + relative_path;
    SDL_Surface* loaded_surface = IMG_Load(full_path.c_str());
    if (loaded_surface == NULL)
    {
        std::cerr << "Error loading image " << full_path << " ! SDL_image error: " << IMG_GetError() << std::endl;
    }
    return loaded_surface;
}
