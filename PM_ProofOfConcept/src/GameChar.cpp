#include "../header/GameChar.h"

#include <iostream>
#include <cmath>

GameChar::GameChar(std::string name, int type_id, vec2d init_loc, WorldSpace* world) :
	name(name), type_id(type_id), loc(init_loc), dest(init_loc), world(world)
{
	this->hitbox = rect();
	this->cardinal = cardinaldir::SOUTH;
	this->animation_timer = SDL_GetTicks();
}

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

	rapidjson::Value anim_data = JsonRepo::get_jobject(char_template, "Animations");
	animations = Animation::load_animations(dir_path, &anim_data, img_repo);

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

SDL_Texture* GameChar::current_sprite()
{
	if (anim_index == -1)
		return static_sprite;
	return animations[anim_index].current_frame();
}

Animation GameChar::play_animation(std::string aname)
{
	//check if we have an animation in the list that matches the name, if we d
}

//Move in the direction of the point (x, y) with steps of size [spd]
void GameChar::move_towards(vec2d d, float spd)
{
	//calculate displacement vector
	vec2d disp = d - loc;

	vec2d new_loc = vec2d();
	if (disp.length() <= spd) {
		new_loc = d;
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
	vec2d center_dest = d - centroid;
	vec2d disp = center_dest - loc;
	this->cardinal = disp.cardinal();

	if (this->cardinal != cardinaldir::NODIR)
	{
		anim_index = (int)cardinal + 1;
	}
	dest = d - centroid;
}

void GameChar::advance_animation()
{
	if (anim_index >= 0)
	{
		animations[anim_index].advance_frame();
	}
}

void GameChar::update(float speedmult)
{
	if (anim_index >= 0)
	{
		if (loc == dest)
		{
			anim_index = 0;
		}
		Uint32 interval = SDL_GetTicks() - animation_timer;
		if (interval > animations[anim_index].frame_interval())
		{
			advance_animation();
			animation_timer = SDL_GetTicks();
		}
	}

	if (loc != dest)
	{
		move_towards(dest, speedmult);
	}
}

void GameChar::render(SDL_Renderer* renderer)
{
	SDL_Rect dstrect;
	dstrect.x = (int)round((loc - centroid).get_x());
	dstrect.y = (int)round((loc - centroid).get_y());
	dstrect.w = 30; // hitbox.width;
	dstrect.h = 30; // hitbox.height;

	SDL_Rect char_outline = { (int)round((loc - centroid).get_x()), (int)round((loc - centroid).get_y()), 30, 30 };
	SDL_SetRenderDrawColor(renderer, 0, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);

	SDL_RenderCopy(renderer, current_sprite(), NULL, &dstrect);
	SDL_RenderDrawRect(renderer, &char_outline);
}
