#include "../header/ImageRepo.h"

#include <SDL2/SDL_image.h>

#include <iostream>

ImageRepo::ImageRepo(SDL_Renderer* gRenderer)
{
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
    flush_cache();
}

void ImageRepo::flush_cache()
{
    std::map<std::string, SDL_Texture*>::iterator it;
    for (it = image_cache.begin(); it != image_cache.end(); it++)
    {
        SDL_DestroyTexture(it->second);
    }
    image_cache.clear();
}

SDL_Surface* ImageRepo::loadSurface(std::string relative_path)
{
    SDL_Surface* loaded_surface = IMG_Load(relative_path.c_str());
    if (loaded_surface == NULL)
    {
        std::cerr << "Error loading image " << relative_path << " ! SDL_image error: " << IMG_GetError() << std::endl;
    }
    return loaded_surface;
}

SDL_Texture* ImageRepo::loadTexture(std::string relative_path)
{
    auto it = image_cache.find(relative_path);
    if (it == image_cache.end())
    {
        SDL_Texture* tex = NULL;
        SDL_Surface* loaded_surface = loadSurface(relative_path);
        if (loaded_surface != NULL) {
            tex = SDL_CreateTextureFromSurface(renderer, loaded_surface);
            if (tex == NULL)
            {
                std::cerr << "Unable to create texture from " << ASSETS_DIR + relative_path << " ! SDL Error: " << SDL_GetError() << std::endl;
            }
            //SDL_FreeSurface(loaded_surface); 
        }
        it = image_cache.insert(it, std::make_pair(relative_path, tex));
    }
    return it->second;
}


SDL_Texture* ImageRepo::loadTexture(std::string asset_subdir, std::string fname)
{
    std::string fpath = ASSETS_DIR + asset_subdir + "/" + fname + PNG_EXTENSION;
    return loadTexture(fpath);
}

SDL_Texture* ImageRepo::loadTexture(std::vector<std::string> asset_subdirs, std::string fname)
{
    std::string fpath = ASSETS_DIR;
    for (std::string subdir : asset_subdirs)
    {
        fpath += subdir + "/";
    }
    fpath += fname + PNG_EXTENSION;
    return loadTexture(fpath);
}