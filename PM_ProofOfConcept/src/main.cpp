#include <SDL2/SDL.h>
#include <stdio.h>

#include <string>
#include <vector>
#include <iostream>
#include <nlohmann/json.hpp>

#include "../header/Color.h"
#include "../header/Game.h"
#include "../header/Util.h"
#include "../header/GameChar.h"
#include "../header/WorldSpace.h"
#include "../header/ImageRepo.h"

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

	location start_loc;
	start_loc.x = 30;
	start_loc.y = 30;

	

	if (!init_game(gWindow, gRenderer, ImageRepo, "", world, WINDOW_WIDTH, WINDOW_HEIGHT))
	{
		std::cerr << "Failed to initialize" << std::endl;
	}
	else
	{
		bool quit = false;
		bool click = false;
		SDL_Event e;

		GameChar* slime = new GameChar("Slime", "SlimeTest", start_loc, world, ImageRepo);

		while (!quit)
		{
			while (SDL_PollEvent(&e) != 0)
			{
				switch (e.type) {
				case SDL_QUIT:
					quit = true;
					break;
				case SDL_MOUSEBUTTONDOWN:
					click = true;
					break;
				case SDL_MOUSEBUTTONUP:
					click = false;
					break;
				}
			}
			if (click) {
				int mouse_x, mouse_y;
				SDL_GetMouseState(&mouse_x, &mouse_y);
				slime->move_towards(mouse_x, mouse_y, 0.25);
			}
			SDL_RenderClear(gRenderer);
			slime->draw_character(gRenderer);
			SDL_RenderPresent(gRenderer);
		}
	}	
	close(gWindow, world);
	return 0;
}
