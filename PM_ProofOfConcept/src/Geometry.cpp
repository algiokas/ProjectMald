#include "..\header\Geometry.h"

//when updating any of the vector components, we set len to -1 so that length() recalculates it
void vec2d::set_x(float new_x)
{
	x = new_x;
	len = -1;
}

void vec2d::set_y(float new_y)
{
	y = new_y;
	len = -1;
}

vec2d vec2d::normal()
{
	return *this / length();
}

//if length hasn't already been calculated, calculate it and store it in len
float vec2d::length()
{
	if (len < 0)
	{
		len = (float)sqrt((x * x) + (y * y));
	}
	return len;
}

bool vec2d::operator ==(const vec2d& rhs)
{
	return this->x == rhs.x && this->y == rhs.y;
}

bool vec2d::operator !=(const vec2d& rhs)
{
	return !(*this == rhs);
}

vec2d& vec2d::operator +=(const vec2d& rhs)
{
	this->x += rhs.x;
	this->y += rhs.y;
	return *this;
}

vec2d& vec2d::operator -=(const vec2d& rhs)
{
	this->x -= rhs.x;
	this->y -= rhs.y;
	return *this;
}

vec2d& vec2d::operator *=(const float& rhs)
{
	this->x *= rhs;
	this->y *= rhs;
	return *this;
}

vec2d& vec2d::operator /=(const float& rhs)
{
	this->x /= rhs;
	this->y /= rhs;
	return *this;
}