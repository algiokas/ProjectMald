#include "../header/GameChar.h"
#include "../header/ImageRepo.h"

#include <iostream>
#include <cmath>

GameChar::GameChar(std::string name, std::string asset_dir, point2d init_loc, WorldSpace* world, ImageRepo* loader)
{
	this->name = name;
	this->asset_dir = asset_dir;
	this->loc = init_loc;
	this->world = world;
	this->loader = loader;

	load_sprites();
}

GameChar::~GameChar()
{
	for (SDL_Texture* s : sprites)
	{
		SDL_DestroyTexture(s);
		s = NULL;
	}
}

void GameChar::load_sprites()
{
	//TODO load sprites based on asset_dir
	std::string base_sprite_fname = "Characters/Goimbo/SmallTestCharacterWalkingAnimation";
	for (int i = 1; i < 11; i++) {
		std::string fpath = base_sprite_fname + std::to_string(i) + ".png";
		SDL_Texture* tex = loader->loadTexture(fpath);
		if (tex != NULL)
		{
			sprites.push_back(tex);
		}
	}

	//TEMPORARY
	SDL_QueryTexture(sprites[0], NULL, NULL, &(hitbox.width), &(hitbox.height));
}

point2d GameChar::centroid()
{
	return point2d();
}

point2d Centroid()
{
	point2d centroid;

}

//Move the centerpoint of the character to (x, y)
void GameChar::move_to(float x, float y)
{
	this->loc.x = x - (hitbox.width / 2.0f);
	this->loc.y = y - (hitbox.height / 2.0f);

	//TODO add collision/bounds checking
}

//Move in the direction of the point (x, y) with steps of size [spd]
void GameChar::move_towards(float x, float y, float spd)
{
	//location of the hitbox centroid relative to the top left corner
	point2d centroid;
	centroid.x = hitbox.width / 2.0f;
	centroid.y = hitbox.height / 2.0f;

	//calculate displacement vector
	float disp_x = x - (this->loc.x + centroid.x);
	float disp_y = y - (this->loc.y + centroid.y);

	//Get length of displacement vector
	float disp_length = (float)sqrt((disp_x * disp_x) + (disp_y * disp_y));

	float new_x, new_y;
	if (disp_length <= spd) {
		new_x = x - centroid.x;
		new_y = y - centroid.y;
	}
	else
	{
		//get new location value by adding normalized displacement vector multiplied by movespeed
		new_x = this->loc.x + spd * (disp_x / disp_length);
		new_y = this->loc.y + spd * (disp_y / disp_length);
	}
	//std::cout << "Move To: (" << new_x << ", " << new_y << ")" << std::endl;
	
	if (!world->check_collision_x(new_x, new_x + this->hitbox.width)) {
		this->loc.x = new_x;
	}
	if (!world->check_collision_y(new_y, new_y + this->hitbox.height)) {
		this->loc.y = new_y;
	}
}

void GameChar::set_destination(point2d d)
{
	dest = d;
}

void GameChar::update()
{
	if (loc != dest)
	{
		move_towards(dest.x, dest.y, 0.5);
	}
}

//Draw the character's current sprite state onto the destination surface
void GameChar::render(SDL_Renderer* renderer)
{
	SDL_Rect dstrect;
	dstrect.x = (int)round(this->loc.x);
	dstrect.y = (int)round(this->loc.y);
	dstrect.w = 32; // hitbox.width;
	dstrect.h = 32; // hitbox.height;

	SDL_RenderCopy(renderer, sprites[0], NULL, &dstrect);
}
