#include <SDL.h>
#include <stdio.h>

#include <string>
#include <vector>
#include <iostream>
#include <nlohmann/json.hpp>

#include "../header/Game.h"
#include "../header/Util.h"
#include "../header/Character.h"
#include "../header/WorldSpace.h"

//constants
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

int main(int argc, char* argv[])
{
	//The window we'll be rendering to
	SDL_Window *gWindow = NULL;
	SDL_Surface* gWindowSurface = NULL;
	SDL_Surface* gImgSurface = NULL;

	location start_loc;
	start_loc.x = 0;
	start_loc.y = 0;

	rect hit_box;
	hit_box.width = 12;
	hit_box.height = 10;

	WorldSpace* world = new WorldSpace(WINDOW_WIDTH, WINDOW_HEIGHT, 5);
	Character* slime = new Character("Slime", "SlimeTest", start_loc, hit_box, world);

	if (!init_game(gWindow, gWindowSurface, WINDOW_WIDTH, WINDOW_HEIGHT))
	{
		std::cerr << "Failed to initialize" << std::endl;
	}
	else
	{
		const char* filepath = "assets/SlimeTest/Movement1.bmp";
		if (!load_image(gImgSurface, filepath))
		{
			std::cerr << "Failed to Load Image" << std::endl;
		}
		else
		{
			bool quit = false;
			bool click = false;
			SDL_Event e;
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
				SDL_FillRect(gWindowSurface, NULL, SDL_MapRGB(gWindowSurface->format, 0xFF, 0xFF, 0xFF));
				slime->draw_character(gWindowSurface);
				SDL_UpdateWindowSurface(gWindow);
			}
		}
	}
	
	std::vector<SDL_Surface*> all_surfaces;
	all_surfaces.push_back(gImgSurface);
	close(gWindow, all_surfaces);
	return 0;
}