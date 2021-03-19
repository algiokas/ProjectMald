#pragma once

#include <SDL2/SDL.h>

#include "Geometry.h"

//base class for objects that collide with each other and the game world
class Collider {	
protected:
	SDL_Rect hitbox;

public:
	//check collision of two colliders
	bool check_collision(Collider* other);

	//check if this object intersects the inside of a rectangular region
	bool check_collision_inner(SDL_Rect other_hbox);
	bool check_collision_inner(float x, float y, float w, float h);

	//check if this object intersects the outside of a rectangular region
	bool check_collision_outer(SDL_Rect other_hbox);
	bool check_collision_outer(float x, float y, float w, float h);

};