#pragma once

#include <vector>

#include "GameChar.h"

class WorldSpace
{
	int width;
	int height;
	int margin;
	std::vector<GameChar*> all_characters;

public:
	WorldSpace(int width, int height, int margin);
	~WorldSpace();
	bool check_collision_x(float x1, float x2);
	bool check_collision_y(float y1, float y2);
	void add_character(GameChar* new_char);
};