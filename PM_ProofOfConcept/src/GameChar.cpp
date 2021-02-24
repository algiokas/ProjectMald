#include "../header/GameChar.h"
#include "../header/ImageRepo.h"

#include <iostream>
#include <cmath>

GameChar::GameChar(std::string name, std::string asset_dir, location init_loc, WorldSpace* world, ImageRepo* loader)
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
	std::string base_sprite_fname = "SmallTestCharacterWalkingAnimation";
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

//Move the centerpoint of the character to (x, y)
void GameChar::move_to(float x, float y)
{
	float new_x = x - (hitbox.width / 2.0f);
	if (new_x > 5 && new_x < (640 ))
	this->loc.x =
	this->loc.y = y - (hitbox.height / 2.0f);

	//TODO add collision/bounds checking
}

//Move in the direction of the point (x, y) with steps of size [spd]
void GameChar::move_towards(int x, int y, float spd)
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

	//DEBUG
	//std::cout << "Move To: (" << new_x << ", " << new_y << ")" << std::endl;
	
	if (!world->check_collision_x(new_x, new_x + this->hitbox.width)) {
		this->loc.x = new_x;
	}
	if (!world->check_collision_y(new_y, new_y + this->hitbox.height)) {
		this->loc.y = new_y;
	}
}

//Draw the character's current sprite state onto the destination surface
void GameChar::draw_character(SDL_Renderer* renderer)
{
	SDL_Rect dstrect;
	dstrect.x = (int)round(this->loc.x);
	dstrect.y = (int)round(this->loc.y);
	dstrect.w = 64; // hitbox.width * 3;
	dstrect.h = 64; // hitbox.height * 3;

	SDL_RenderCopy(renderer, sprites[0], NULL, &dstrect);
}
