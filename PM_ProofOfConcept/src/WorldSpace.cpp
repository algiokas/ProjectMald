#include "../header/WorldSpace.h"

WorldSpace::WorldSpace(int width, int height, int margin)
{
	this->width = width;
	this->height = height;
	this->margin = margin;
}

WorldSpace::~WorldSpace()
{
	for (GameChar* c : all_characters)
	{
		delete c;
	}
}

bool WorldSpace::check_collision_x(float x1, float x2)
{
	return (x1 < margin && x2 >= width - margin);
}

bool WorldSpace::check_collision_y(float y1, float y2)
{
	return (y1 < margin && y2 >= height - margin);
}

void WorldSpace::add_character(GameChar* new_char)
{
	all_characters.push_back(new_char);
}
