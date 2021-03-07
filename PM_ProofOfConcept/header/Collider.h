#pragma once

#include "Geometry.h"

//base class for objects that collide with each other and the game world
class Collider {

	Collider(); //private constructor
	virtual ~Collider() = 0;
protected:
	vec2d loc;
	rect hitbox;

public:
	//check collision of two colliders
	bool check_collision(Collider* other);

	//check if this object intersects the inside of a rectangular region
	bool check_collision_inner(float x, float y, float w, float h);

	//check if this object intersects the outside of a rectangular region
	bool check_collision_outer(float x, float y, float w, float h);
};