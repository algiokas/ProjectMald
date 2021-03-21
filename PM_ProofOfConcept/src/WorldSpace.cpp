#include "../header/WorldSpace.h"
#include "../header/repository/JsonRepo.h"

#include <iostream>

bool WorldSpace::world_collision(SDL_Rect hitbox)
{
	return false;
}

WorldSpace::~WorldSpace()
{
	for (GameChar* c : all_characters)
	{
		delete c;
	}
}

WorldSpace* WorldSpace::CreateWorld(JsonRepo* json_repo, ImageRepo* img_repo, SDL_Renderer* renderer)
{
	using json = nlohmann::json;

	try
	{
		int width, height, margin;
		float speedmult;
		color bg_color;
		SDL_Texture* bg_img = NULL;

		WorldSpace* brave_new_world;

		//TODO - Improve error checking for  JSON loading
		json world_data = json_repo->get_map_data();
		if (world_data == NULL)
		{
			std::cerr << "World loading failed" << std::endl;
			return NULL;
		}

		margin = JsonRepo::get_int(world_data, "Margin", 5);
		speedmult = JsonRepo::get_float(world_data, "Speedmult", 0.1);
		auto dims_it = world_data.find("Dimensions");
		if (dims_it != world_data.end())
		{
			width = JsonRepo::get_int(dims_it.value(), "width", 0);
			height = JsonRepo::get_int(dims_it.value(), "height", 0);
		}

		std::string color_str = JsonRepo::get_string(world_data, "Backgroundcolor", "BLACK");
		auto it = COLORS.find(color_str);
		if (it != COLORS.end())
		{
			bg_color = it->second;
		}

		std::string bg_string = JsonRepo::get_string(world_data, "Backgroundimage", "");
		if (bg_string.length() > 0)
		{
			bg_img = img_repo->loadTexture("Background", bg_string);
		}

		WorldSpace* brave_new_world = new WorldSpace(width, height, margin, speedmult, bg_color, bg_img, renderer);

		JArray c_array = JsonRepo::get_jarray(world_data, "Characters");
		for (auto arr_itr = c_array.Begin(); arr_itr != c_array.End(); arr_itr++)
		{
			if (arr_itr->IsObject())
			{
				Value char_data = arr_itr->GetObject();
				std::string t_name = JsonRepo::get_string(&char_data, "Name", "");
				int t_id = JsonRepo::get_int(&char_data, "ID", -1);
				JArray t_loc = JsonRepo::get_jarray(&char_data, "Location");

				vec2d new_loc(0.0, 0.0);
				if (t_loc.Size() > 0)
				{
					if (t_loc[0].IsInt())
					{
						new_loc.set_x(t_loc[0].GetInt());
					}
					if (t_loc.Size() > 1 && t_loc[1].IsInt())
					{
						new_loc.set_y(t_loc[1].GetInt());
					}
				}
				GameChar* t_char = GameChar::create_character(t_name, t_id, new_loc, brave_new_world, json_repo, img_repo);
				brave_new_world->add_character(t_char);
			}
		}
	}
	catch (const std::exception& ex)
	{

	}

	return brave_new_world;
}

bool WorldSpace::check_collision(GameChar* c)
{
	return false;
}

bool WorldSpace::check_collision_move(GameChar* c, SDL_Rect new_hitbox)
{
	return false;
}

GameChar* WorldSpace::get_pc()
{
	return player_character;
}

void WorldSpace::add_character(GameChar* new_char)
{
	all_characters.push_back(new_char);

	if (all_characters.size() == 1) {
		player_character = all_characters[0];
	}
}

void WorldSpace::update()
{
	for (auto c : all_characters)
	{
		c->update(speedmult);
	}
}

void WorldSpace::render()
{
	SDL_SetRenderDrawColor(renderer, bg_color.r, bg_color.g, bg_color.b, 0xFF); 
	SDL_RenderClear(renderer);
	if (bg_texture != NULL)
	{
		SDL_RenderCopy(renderer, bg_texture, NULL, NULL);
	}

	for (GameChar* c : all_characters)
	{
		c->render(renderer);
	}	
	SDL_RenderPresent(renderer);
}
