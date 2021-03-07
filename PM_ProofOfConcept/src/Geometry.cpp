#include "..\header\Geometry.h"

bool equal_relative(float a, float b, float maxDiffRel = FLT_EPSILON)
{
	if ((a < 0) != (b < 0)) return false; //check if they have the same sign
	float delta = std::abs(a - b);
	if (delta == 0.0f) return true;

	float max = (std::abs(a) > std::abs(b)) ? std::abs(a) : std::abs(b);
	if (delta <= max * maxDiffRel)
		return true;
	return false;
}

vec2d vec2d::normal()
{
	return this->scale(1.0);
}

vec2d vec2d::scale(float new_length)
{
	float scaling_ratio = new_length / len;
	return (*this) * scaling_ratio;
}

void vec2d::resize(float new_length)
{
	float scaling_ratio = new_length / len;
	x *= scaling_ratio;
	y *= scaling_ratio;
}


bool vec2d::is_collinear(vec2d v)
{
	float x_ratio = this->x / v.x;
	float y_ratio = this->y / v.y;
	return equal_relative(x_ratio, y_ratio);
}

float vec2d::length()
{
	if (len < 0)
	{
		len = (float)sqrt((x * x) + (y * y));
	}
	return len;
}

cardinaldir vec2d::cardinal()
{
	//Note: the y axis is flipped in this case. that is, an increase in the value of Y
	// indicates "down" rather than up as in a regular cartesian coordinate system
	if (len == 0) return cardinaldir::NODIR;
	if (y <= std::abs(x) * -1) return cardinaldir::NORTH;
	if (x > std::abs(y)) return cardinaldir::EAST;	
	if (y >= std::abs(x)) return cardinaldir::SOUTH;
	if (x < std::abs(y) * -1) return cardinaldir::WEST;
	return cardinaldir::NODIR;
}

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