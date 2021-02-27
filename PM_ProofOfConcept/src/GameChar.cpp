#include "../header/GameChar.h"

#include <iostream>
#include <cmath>

#include <rapidjson/document.h>

GameChar* GameChar::CreateCharacter(std::string name, int id, vec2d init_loc, WorldSpace* world, 
									JsonRepo* json_repo, ImageRepo* img_repo)
{
	std::string t_name;
	auto all_char_data = json_repo->get_char_data();
	auto char_template = json_repo->get_by_id(all_char_data, id, &t_name);
	if (!char_template.IsNull())
	{
		//TODO - load other character stats from JSON here
		GameChar* new_char = new GameChar(name, id, init_loc, world);
		new_char->load_sprites(img_repo, t_name, &char_template);
		return new_char;
	}
	return NULL;
}

void GameChar::load_sprites(ImageRepo* img_repo, std::string template_name, rapidjson::Value* char_template)
{
	std::string static_img_fname = JsonRepo::get_string(char_template, "Staticimage", "CHARACTER_PH");
	std::vector<std::string> dir_path = { "Characters", template_name };
	static_sprite = img_repo->loadTexture(dir_path, static_img_fname);

	rapidjson::Value animations = JsonRepo::get_jobject(char_template, "Animations");
	sprites = Animation::load_animations(dir_path, &animations, img_repo);

	//Set hitbox dimensions to the dimensions of the character's static sprite
	SDL_QueryTexture(static_sprite, NULL, NULL, &hitbox.width, &hitbox.height);

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

SDL_Texture* GameChar::get_current_sprite()
{
	if (current_animation == NULL)
		return static_sprite;
	return current_animation->get_current_frame();
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
	
	if (!world->check_collision_x(new_loc.get_x(), new_loc.get_x() + hitbox.width)) {
		loc.set_x(new_loc.get_x());
	}
	if (!world->check_collision_y(new_loc.get_y(), new_loc.get_y() + hitbox.height)) {
		loc.set_y(new_loc.get_y());
	}
}

void GameChar::set_destination(vec2d d)
{
	dest = d - centroid;
}

void GameChar::update(float speedmult)
{
	if (loc != dest)
	{
		move_towards(dest, speedmult);
	}
}

//Draw the character's current sprite state onto the destination surface
void GameChar::render(SDL_Renderer* renderer)
{
	SDL_Rect dstrect;
	dstrect.x = (int)round(loc.get_x());
	dstrect.y = (int)round(loc.get_y());
	dstrect.w = 32; // hitbox.width;
	dstrect.h = 32; // hitbox.height;

	SDL_RenderCopy(renderer, get_current_sprite(), NULL, &dstrect);
}
