#include "../header/WorldSpace.h"
#include "../header/JsonRepo.h"

#include <iostream>

WorldSpace::~WorldSpace()
{
	for (GameChar* c : all_characters)
	{
		delete c;
	}
}

WorldSpace* WorldSpace::CreateWorld(JsonRepo* json_repo, ImageRepo* img_repo, SDL_Renderer* renderer)
{
	int width, height, margin;
	float speedmult;
	color bg_color;
	SDL_Texture* bg_img;

	//TODO - Improve error checking for  JSON loading
	rapidjson::Document* world_data = json_repo->get_map_data();
	if (world_data == NULL)
	{
		std::cerr << "World loading failed" << std::endl;
		return NULL;
	}

	margin = JsonRepo::GetInt(world_data, "Margin", 5);
	speedmult = JsonRepo::GetFloat(world_data, "Speedmult", 0.1);
	auto dims = JsonRepo::GetObject(world_data, "Dimensions");
	if (dims.IsNull())
	{
		width = JsonRepo::GetInt(&dims, "width", 0);
		height = JsonRepo::GetInt(&dims, "height", 0);
	}
	else
	{
		width = height = 0;
	}

	std::string color_str = JsonRepo::GetString(world_data, "Backgroundcolor", "BLACK");
	auto it = COLORS.find(color_str);
	if (it != COLORS.end())
	{
		bg_color = it->second;
	}

	std::string bg_string = JsonRepo::GetString(world_data, "Backgroundimage", "");
	if (bg_string.length() > 0)
	{
		bg_img = img_repo->loadTexture("Background/" + bg_string);
	}

	WorldSpace* brave_new_world = new WorldSpace(width, height, margin, speedmult, bg_color, bg_img, renderer);

	JArray c_array = JsonRepo::GetArray(world_data, "Characters");
	for (auto arr_itr = c_array.Begin(); arr_itr != c_array.End(); arr_itr++)
	{
		if (arr_itr->IsObject())
		{
			Value char_data = arr_itr->GetObject();
			std::string t_name = JsonRepo::GetString(&char_data, "Name", "");
			int t_id = JsonRepo::GetInt(&char_data, "ID", -1);
			JArray t_loc = JsonRepo::GetArray(&char_data, "Location");

			vec2d new_loc(0.0, 0.0);
			if (t_loc.Size() > 0)
			{
				if (t_loc[0].IsFloat())
				{
					new_loc.set_x(t_loc[0].GetFloat());
				}
				if (t_loc.Size() > 1 && t_loc[1].IsFloat())
				{
					new_loc.set_y(t_loc[1].GetFloat());
				}
			}
			GameChar* t_char = GameChar::CreateCharacter(t_name, t_id, new_loc, brave_new_world, json_repo, img_repo);
			brave_new_world->add_character(t_char);
		}
	}
	return brave_new_world;
}

bool WorldSpace::check_collision_x(float x1, float x2)
{
	return (x1 < margin && x2 >= width - margin);
}

bool WorldSpace::check_collision_y(float y1, float y2)
{
	return (y1 < margin && y2 >= height - margin);
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
		c->update();
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
