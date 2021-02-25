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
#include "main.h"

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

		GameChar* goimbo = new GameChar("Goimbo", "SlimeTest", start_loc, world, ImageRepo);
		world->add_character(goimbo);
		while (!quit)
		{
			while (SDL_PollEvent(&e) != 0)
			{
				handle_event(e, quit, click);
			}
			//if (click) {
			//	int mouse_x, mouse_y;
			//	SDL_GetMouseState(&mouse_x, &mouse_y);
			//	slime->move_towards(mouse_x, mouse_y, 0.25);
			//}
			world->render();
		}
	}	
	close(gWindow, world);
	return 0;
}

void handle_keypress(SDL_Event& e, WorldSpace* world)
{
	SDL_Keycode asdf;
	auto keydown = e.key;
	switch (keydown.keysym.sym) {
		case SDLK_UP:



	}

	SDL_KeyboardEvent test;
}

void handle_event(SDL_Event& e, bool& quit, bool& click)
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
		case SDL_KEYDOWN:
			handle_keypress(e);
			break;
	}
}
