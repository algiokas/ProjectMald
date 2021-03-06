#include "../header/GameChar.h"

#include <iostream>
#include <cmath>

static const float BASE_MAX_SPEED = 320;
static const int ACCELERATION_STEPS = 10; //How many steps it takes a character to reach max speed

GameChar::GameChar(std::string name, int type_id, vec2d init_loc, float max_speed, WorldSpace* world) :
	name(name), type_id(type_id), loc(init_loc), dest(init_loc), max_speed(max_speed), world(world)
{
	this->velocity = vec2d();
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
		float ms = BASE_MAX_SPEED * JsonRepo::get_float(&char_template, "Movespeed", 0.0);
		//TODO - load other character stats from JSON here
		GameChar* new_char = new GameChar(name, id, init_loc, ms, world);
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
	if (current_anim.empty())
		return static_sprite;
	return animations[current_anim].current_frame();
}


void GameChar::play_animation(std::string aname)
{
	if (aname != current_anim)
	{
		if (animations.find(aname) != animations.end())
		{
			current_anim = aname;
		}
		else
		{
			current_anim = "";
			std::cerr << "Animation: " << aname << "Not found" << std::endl;
		}
	}
}

void GameChar::move_towards(vec2d d)
{
	//calculate displacement vector
	vec2d disp = d - loc;

	float time_step = movement_timer / 1000;
	float accel_step = 1 / ACCELERATION_STEPS;

	if (velocity.length() < max_speed && !equal_relative(velocity.length(), max_speed))
	{
		vec2d new_velocity = velocity + (velocity.normal() * max_speed * accel_step);
		if (new_velocity.length() > max_speed && !equal_relative(new_velocity.length(), max_speed))
		{
			velocity = velocity.scale(max_speed);
		}
	}
	vec2d new_loc = loc + (velocity * time_step);
	
	if (!world->world_collision_x(new_loc.get_x(), new_loc.get_x() + hitbox.width)) {
		loc.set_x(new_loc.get_x());
	}
	if (!world->world_collision_y(new_loc.get_y(), new_loc.get_y() + hitbox.height)) {
		loc.set_y(new_loc.get_y());
	}
}

void GameChar::set_destination(vec2d d)
{
	vec2d center_dest = d - centroid;
	vec2d disp = center_dest - loc;
	this->cardinal = disp.cardinal();

	switch (cardinal)
	{
	case cardinaldir::NORTH :
		play_animation("WalkNorth");
		break;
	case cardinaldir::EAST :
		play_animation("WalkEast");
		break;
	case cardinaldir::SOUTH :
		play_animation("WalkSouth");
		break;
	case cardinaldir::WEST :
		play_animation("WalkWest");
		break;
	}
	dest = d - centroid;
}

void GameChar::advance_animation()
{
	if (!current_anim.empty())
	{
		animations[current_anim].advance_frame();
	}
}

void GameChar::update(float speedmult)
{
	if (!current_anim.empty())
	{
		if (loc == dest)
		{
			play_animation("Idle");
		}
		Uint32 interval = SDL_GetTicks() - animation_timer;
		if (interval > animations[current_anim].frame_interval())
		{
			advance_animation();
			animation_timer = SDL_GetTicks();
		}
	}

	
	if (loc != dest)
	{
		move_towards(dest);
	}
	movement_timer = 0;
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
