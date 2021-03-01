#include <SDL2/SDL.h>
#include <stdio.h>

#include <string>
#include <vector>
#include <iostream>

#include "../header/Color.h"
#include "../header/Game.h"
#include "../header/Geometry.h"
#include "../header/GameChar.h"
#include "../header/WorldSpace.h"
#include "../header/ImageRepo.h"
#include "../header/EventHandling.h"

int main(int argc, char* argv[])
{
	//The window we'll be rendering to
	SDL_Window *gWindow = NULL;
	SDL_Renderer* gRenderer = NULL;
	ImageRepo* imageRepo = NULL;
	JsonRepo* jsonRepo = NULL;
	WorldSpace* world = NULL;

	if (!init_game(gWindow, gRenderer, imageRepo, jsonRepo, world))
	{
		std::cerr << "Failed to initialize" << std::endl;
	}
	else
	{
		bool quit = false;
		SDL_Event e;
		while (!quit)
		{
			while (SDL_PollEvent(&e) != 0)
			{
				handle_event(e, world, quit);
			}
			world->update();
			world->render();
		}
	}	
	close(gWindow, imageRepo, jsonRepo, world);
	return 0;
}