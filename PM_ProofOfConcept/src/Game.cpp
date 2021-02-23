#include "../header/Game.h"

#include <iostream>
#include <vector>


bool init_game(SDL_Window*& window, SDL_Surface*& surface, int window_width, int window_height)
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        success = false;
    }
    else
    {
        //Create window
        window = SDL_CreateWindow("SDL Blah", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_width, window_height, SDL_WINDOW_SHOWN);
        if (window == NULL)
        {
            std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
            success = false;
        }
        else
        {
            //Get window surface
            surface = SDL_GetWindowSurface(window);
        }
    }
    return success;
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

void close(SDL_Window* window, std::vector<SDL_Surface*> surfaces)
{
	for (SDL_Surface* s : surfaces)
	{
		SDL_FreeSurface(s);
	}
	SDL_DestroyWindow(window);
	SDL_Quit();
}
