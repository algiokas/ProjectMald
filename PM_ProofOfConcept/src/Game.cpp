#include "../header/Game.h"
#include "../header/Color.h"

#include <iostream>

#include <SDL2/SDL_image.h>

bool init_game(SDL_Window*& window, SDL_Renderer*& renderer, AssetLoader*& loader, std::string asset_dir, WorldSpace*& world, int window_width, int window_height)
{
    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    //Create a window
    window = SDL_CreateWindow("Project Mald - PROOF OF CONCEPT", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_width, window_height, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    //Get renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    //Instantiate asset loader
    if (!asset_dir.empty())
    {
        loader = new AssetLoader(renderer, asset_dir);
    }
    else
    {
        loader = new AssetLoader(renderer);
    }

    if (!loader->img_init_success) {
        return false;
    }  

    //Set background color
    SDL_SetRenderDrawColor(renderer, COLOR_BLACK.r, COLOR_BLACK.g, COLOR_BLACK.b, 0xFF);

    world = new WorldSpace(window_width, window_height, 5);

    return true;
}

bool load_image(SDL_Surface*& imgSurface, const char* filepath)
{
	//Loading success flag
	bool success = true;

	//Load splash image
    imgSurface = SDL_LoadBMP(filepath);
	if (imgSurface == NULL)
	{
        std::cerr << "Unable to load image " << filepath << "! SDL Error: " << SDL_GetError() << std::endl;
		success = false;
	}
	return success;
}

void close(SDL_Window* window, WorldSpace* world)
{
    delete world; //MWAHAHAHA

    SDL_DestroyWindow(window);
    window = NULL;

    IMG_Quit();
    SDL_Quit();
}
