#include "../header/Collider.h"

bool Collider::check_collision(Collider* other)
{
	return check_collision_inner(other->hitbox.x, other->hitbox.y, 
								 other->hitbox.x + hitbox.w, other->hitbox.y + hitbox.h);
}

bool Collider::check_collision_inner(SDL_Rect other_hbox)
{
	SDL_Rect result;
	return SDL_IntersectRect(&hitbox, &other_hbox, &result);
}

bool Collider::check_collision_inner(float x, float y, float w, float h)
{
	SDL_Rect result;
	SDL_Rect other = { x, y, w, h };
	return check_collision_inner(other);
}

bool Collider::check_collision_outer(SDL_Rect other_hbox)
{
	return check_collision_outer(other_hbox.x, other_hbox.y, other_hbox.w, other_hbox.h);
}

bool Collider::check_collision_outer(float x, float y, float w, float h)
{
	if (hitbox.x < x) return true;
	if (hitbox.y < y) return true;
	if (hitbox.x + hitbox.w > x + w) return true;
	if (hitbox.y + hitbox.h > y + h) return true;
}
