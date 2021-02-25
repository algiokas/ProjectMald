#include <SDL2/SDL.h>
#include <stdio.h>

#include <string>
#include <vector>
#include <iostream>

#include "../header/Color.h"
#include "../header/Game.h"
#include "../header/Util.h"
#include "../header/GameChar.h"
#include "../header/WorldSpace.h"
#include "../header/ImageRepo.h"
#include "../header/EventHandling.h"

//constants
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

int main(int argc, char* argv[])
{
	//The window we'll be rendering to
	SDL_Window *gWindow = NULL;
	SDL_Renderer* gRenderer = NULL;
	ImageRepo* ImageRepo = NULL;
	WorldSpace* world = NULL;

	point2d start_loc;
	start_loc.x = 30;
	start_loc.y = 30;

	if (!init_game(gWindow, gRenderer, ImageRepo, "", world, WINDOW_WIDTH, WINDOW_HEIGHT))
	{
		std::cerr << "Failed to initialize" << std::endl;
	}
	else
	{
		bool quit = false;
		SDL_Event e;

		GameChar* goimbo = new GameChar("Goimbo", "SlimeTest", start_loc, world, ImageRepo);
		world->add_character(goimbo);
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
	close(gWindow, world);
	return 0;
}