#include "../header/GameChar.h"
#include "../header/ImageRepo.h"

#include <iostream>
#include <cmath>

GameChar::GameChar(std::string name, std::string asset_dir, vec2d init_loc, WorldSpace* world, ImageRepo* image_repo)
{
	this->name = name;
	this->asset_dir = asset_dir;
	this->loc = init_loc;
	this->world = world;
	this->image_repo = image_repo;

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
		SDL_Texture* tex = image_repo->loadTexture(fpath);
		if (tex != NULL)
		{
			sprites.push_back(tex);
		}
	}

	//TEMPORARY
	SDL_QueryTexture(sprites[0], NULL, NULL, &(hitbox.width), &(hitbox.height));

	if (hitbox.width > 0 && hitbox.height > 0)
	{
		centroid.set_x(hitbox.width / 2.0f);
		centroid.set_y(hitbox.height / 2.0f);
	}
	else
	{
		std::cerr << "Invalid sprite hitbox for: " << name << std::endl;
	}
	
}

//Move the centerpoint of the character to (x, y)
void GameChar::move_to(vec2d d)
{
	loc = d - centroid;

	//TODO add collision/bounds checking
}

//Move in the direction of the point (x, y) with steps of size [spd]
void GameChar::move_towards(vec2d d, float spd)
{
	//calculate displacement vector
	vec2d disp = d - (loc + centroid);

	vec2d new_loc = vec2d();
	if (disp.length() <= spd) {
		new_loc = d - centroid;
	}
	else
	{
		//get new location value by adding normalized displacement vector multiplied by movespeed
		new_loc = loc + (disp.normal() * spd);
	}
	//std::cout << "Move To: (" << new_x << ", " << new_y << ")" << std::endl;
	
	if (!world->check_collision_x(new_loc.get_x(), new_loc.get_x() + this->hitbox.width)) {
		loc.set_x(new_loc.get_x());
	}
	if (!world->check_collision_y(new_loc.get_y(), new_loc.get_y() + this->hitbox.height)) {
		loc.set_y(new_loc.get_y());
	}
}

void GameChar::set_destination(vec2d d)
{
	dest = d - centroid;
}

void GameChar::update()
{
	if (loc != dest)
	{
		move_towards(dest, 0.075);
	}
}

//Draw the character's current sprite state onto the destination surface
void GameChar::render(SDL_Renderer* renderer)
{
	SDL_Rect dstrect;
	dstrect.x = (int)round(this->loc.get_x());
	dstrect.y = (int)round(this->loc.get_y());
	dstrect.w = 32; // hitbox.width;
	dstrect.h = 32; // hitbox.height;

	SDL_RenderCopy(renderer, sprites[0], NULL, &dstrect);
}
