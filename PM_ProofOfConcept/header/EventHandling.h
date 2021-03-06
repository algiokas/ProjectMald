#pragma once

#include "../header/WorldSpace.h"

void handle_event(SDL_Event& e, WorldSpace* world, bool& quit);

void handle_keypress(SDL_Event& e, WorldSpace* world);

void handle_mouseclick(SDL_Event& e, WorldSpace* world);

void handle_leftclick(vec2d click_loc, WorldSpace* world);

void handle_rightclick(vec2d click_loc, WorldSpace* world);
