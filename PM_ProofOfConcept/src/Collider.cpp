#include "../header/Collider.h"

bool Collider::check_collision(Collider* other)
{
	return check_collision_inner(other->loc.get_x(), other->loc.get_y(), 
								 other->hitbox.width, other->hitbox.width);
}

bool Collider::check_collision_inner(float x, float y, float w, float h)
{
	bool x_collision = (loc.get_x() > x && loc.get_x() < x + w) ||
		(loc.get_x() + hitbox.width > x &&
			loc.get_x() + hitbox.width < x + w);

	bool y_collision = (loc.get_y() > y && loc.get_y() < y + h) ||
		(loc.get_y() + hitbox.width > y &&
			loc.get_y() + hitbox.width < y + h);
	return 
}

bool Collider::check_collision_outer(float x, float y, float w, float h)
{
	return false;
}
