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

	Value::ConstMemberIterator doc_itr = world_data->FindMember("Dimensions");
	if (doc_itr != world_data->MemberEnd())
	{
		auto dims = doc_itr->value.GetObject();
		Value::ConstMemberIterator obj_itr = dims.FindMember("width");
		if (obj_itr != world_data->MemberEnd()) { width = obj_itr->value.GetInt(); }
		obj_itr = dims.FindMember("height");
		if (obj_itr != world_data->MemberEnd()) { width = obj_itr->value.GetInt(); }
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

	Value::ConstMemberIterator doc_itr = world_data->FindMember("Characters");
	if (doc_itr != world_data->MemberEnd())
	{
		auto c_array = doc_itr->value.GetArray();
		for (int i = 0; i < c_array.Capacity(); i++) {
			auto char_data = c_array[i].GetObject();
			std::string t_name = char_data["Name"].GetString();
			int t_id = char_data["ID"].GetInt();
			auto t_loc = char_data["Location"].GetArray();

			GameChar* t_char = GameChar::CreateCharacter(t_name, t_id, vec2d(t_loc[0].GetFloat(), t_loc[1].GetFloat()), 
														 brave_new_world, json_repo, img_repo);
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
