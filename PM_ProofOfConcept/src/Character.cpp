#include "../header/Character.h"

#include <iostream>
#include <cmath>

Character::Character(std::string name, std::string asset_dir, location init_loc, rect hbox, WorldSpace* world)
{
	this->name = name;
	this->asset_dir = asset_dir;
	this->loc = init_loc;
	this->hitbox = hbox;
	this->world = world;

	load_sprites();
}

void Character::load_sprites()
{
	//TODO load sprites based on asset_dir
	std::string fpath = "assets/" + asset_dir + "/Movement1.bmp";
	SDL_Surface* sprite = SDL_LoadBMP(fpath.c_str());
	if (sprite == NULL)
	{
		std::cerr << "Unable to load image " << fpath << "! SDL Error: " << SDL_GetError() << std::endl;
	}
	this->sprites.push_back(sprite);
}

//Move the centerpoint of the character to (x, y)
void Character::move_to(float x, float y)
{
	float new_x = x - (hitbox.width / 2.0f);
	if (new_x > 5 && new_x < (640 ))
	this->loc.x =
	this->loc.y = y - (hitbox.height / 2.0f);

	//TODO add collision/bounds checking
}

//Move in the direction of the point (x, y) with steps of size [spd]
void Character::move_towards(int x, int y, float spd)
{
	//TODO add custom step length, either via parameter or using a class field

	//calculate displacement vector
	int disp_x = x - (int)round(this->loc.x + (hitbox.width / 2.0f));
	int disp_y = y - (int)round(this->loc.y + (hitbox.height / 2.0f));

	//Get length of displacement vector
	float disp_length = (float)sqrt((disp_x * disp_x) + (disp_y * disp_y));
	if (disp_length < 1) {
		return;
	}

	//get new location value by adding normalized displacement vector multiplied by movespeed
	float new_x = this->loc.x + spd * (disp_x / disp_length);
	float new_y = this->loc.y + spd * (disp_y / disp_length);
	
	if (!world->check_collision_x(new_x, new_x + this->hitbox.width)) {
		this->loc.x = new_x;
	}
	if (!world->check_collision_y(new_y, new_y + this->hitbox.height)) {
		this->loc.y = new_y;
	}
}

//Draw the character's current sprite state onto the destination surface
void Character::draw_character(SDL_Surface* dest)
{
	SDL_Rect srcrect;
	srcrect.x = 10;
	srcrect.y = 6;
	srcrect.w = hitbox.width;
	srcrect.h = hitbox.height;

	SDL_Rect dstrect;
	dstrect.x = (int)round(this->loc.x);
	dstrect.y = (int)round(this->loc.y);

	SDL_BlitSurface(this->sprites[0], &srcrect, dest, &dstrect);
}
