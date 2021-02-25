#pragma once

struct point2d
{
	float x;
	float y;

	bool operator ==(const point2d& rhs) const
	{
		return this->x == rhs.x && this->y == rhs.y;
	}

	bool operator !=(const point2d& rhs) const
	{
		return !(*this == rhs);
	}
};



struct rect
{
	int width;
	int height;
};
