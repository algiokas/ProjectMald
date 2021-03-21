#pragma once

#include <cmath>
#include <string>
#include <float.h>
#include <map>

enum class cardinaldir : int
{
	NORTH, WEST, SOUTH, EAST, NODIR
};

const std::map<cardinaldir, std::string> cardinal_names = {
	{cardinaldir::NORTH, "North"},
	{cardinaldir::WEST, "West"},
	{cardinaldir::SOUTH, "South"},
	{cardinaldir::EAST, "East"} };

const std::map<std::string, cardinaldir> cardinal_values = {
	{ "North", cardinaldir::NORTH },
	{ "West", cardinaldir::WEST },
	{"South", cardinaldir::SOUTH },
	{"East", cardinaldir::EAST, } };
//checks whether two floats are approximately equal relative to their size
bool equal_relative(float a, float b, float maxDiffRel = FLT_EPSILON);

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

	//Get the length of this vector
	float length();

	//Get a copy of this vector with length 1
	vec2d normal();

	//Get a copy of this vector with length [new_length]
	vec2d scale(float new_length);

	//Modify this vector to have length [new_length]
	void resize(float new_length);

	//check if two vectors point in the same direction
	bool is_collinear(vec2d v);

	//Get the cardinal direction of a 2d vector
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
