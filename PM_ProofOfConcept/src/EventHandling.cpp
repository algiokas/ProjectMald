#include "../header/EventHandling.h"

#include <SDL2/SDL.h>

#include <iostream>

void handle_event(SDL_Event& e, WorldSpace* world, bool& quit)
{
	switch (e.type) {
	case SDL_QUIT:
		quit = true;
		break;
	case SDL_MOUSEBUTTONDOWN:
		handle_mouseclick(e, world);
		break;
	case SDL_KEYDOWN:
		handle_keypress(e, world);
		break;
	//default:
	//	std::cerr << "Unhandled SDL_Event of type: " << e.type << std::endl;
	}
}

void handle_mouseclick(SDL_Event& e, WorldSpace* world)
{
	vec2d click_loc((float)e.button.x, (float)e.button.y);

	switch (e.button.button)
	{
	case SDL_BUTTON_LEFT:
		handle_leftclick(click_loc, world);
		break;
	case SDL_BUTTON_RIGHT:
		handle_rightclick(click_loc, world);
		break;
	default:
		std::cerr << "Unhandled SDL_MouseButtonEvent for mouse button: " << e.button.button << std::endl;
	}
}

void handle_leftclick(vec2d click_loc, WorldSpace* world)
{
	world->get_pc()->set_destination(click_loc);
}

void handle_rightclick(vec2d click_loc, WorldSpace* world)
{
	handle_leftclick(click_loc, world); //TODO implement unique right click logic
}

void handle_keypress(SDL_Event& e, WorldSpace* world)
{
	auto keydown = e.key;
	switch (keydown.keysym.sym) {
	case SDLK_i:
		std::cout << "OPEN INVENTORY" << std::endl;
		break;
	}
}

