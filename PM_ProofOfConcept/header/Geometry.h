#pragma once

#include <cmath>

enum class cardinaldir : int
{
	NORTH, WEST, SOUTH, EAST, NODIR
};

//char** CARDINAL_NAMES = { "North", "West", "South", "East" }

class vec2d
{
	float x;
	float y;
	float len;

public:
	vec2d() : x(0), y(0), len(-1) {}
	vec2d(float x, float y) : x(x), y(y), len(-1) {}
	bool operator==(const vec2d& rhs);
	bool operator!=(const vec2d& rhs);
	vec2d& operator+=(const vec2d& rhs);
	vec2d& operator-=(const vec2d& rhs);
	vec2d& operator*=(const float& rhs);
	vec2d& operator/=(const float& rhs);
	float get_x() { return x; }
	float get_y() { return y; }
	void set_x(float new_x);
	void set_y(float new_y);

	float length();
	vec2d normal();
	cardinaldir cardinal();
};

inline vec2d operator+(vec2d lhs, const vec2d& rhs)
{
	lhs += rhs;
	return lhs;
}

inline vec2d operator-(vec2d lhs, const vec2d& rhs)
{
	lhs -= rhs;
	return lhs;
}

inline vec2d operator*(vec2d lhs, const float& rhs)
{
	lhs *= rhs;
	return lhs;
}

inline vec2d operator/(vec2d lhs, const float& rhs)
{
	lhs /= rhs;
	return lhs;
}

struct rect
{
	int width;
	int height;
};
