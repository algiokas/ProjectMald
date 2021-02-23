#pragma once

#include "WorldSpace.h"

class WorldSpace
{
	int width;
	int height;
	int margin;

public:
	WorldSpace(int width, int height, int margin);
	bool check_collision_x(float x1, float x2);
	bool check_collision_y(float y1, float y2);
};