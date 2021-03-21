#include "..\..\header\repository\JsonRepo.h"

#include <cstdio>
#include <string>
#include <iostream>
#include <fstream>

using json = nlohmann::json;

JsonRepo::~JsonRepo()
{
	json_cache.clear();
}

std::unique_ptr<json> JsonRepo::load_json(std::string filepath)
{
	std::ifstream ifile(filepath);

	std::unique_ptr<json> jdoc(new json());

	(*jdoc) = json::parse(ifile);

	return jdoc;
}

json JsonRepo::get_game_data(std::string filename)
{
	if (json_cache.find(filename) == json_cache.end())
	{
		//TODO - centralize location of assets directory data
		std::string fpath = ASSETS_DIR + filename + JSON_EXT;
		try {
			auto jdoc = load_json(fpath);
			json_cache.insert(std::make_pair(filename, jdoc));
		}
		catch (json::parse_error& e)
		{
			std::cerr << "Unable to parse " << fpath << " : Invalid JSON - " << e.what() << std::endl;
		}
	}
	return *(json_cache[filename]);
}

json JsonRepo::get_game_settings()
{
	return get_game_data("Settings");
}

json JsonRepo::get_char_data()
{
	return get_game_data("CharacterData");
}

json JsonRepo::get_item_data()
{
	return get_game_data("ItemData");
}

json JsonRepo::get_map_data()
{
	return get_game_data("Map");
}

nlohmann::json JsonRepo::get_by_id(nlohmann::json root, int id)
{
	std::string s;
	return get_by_id(root, id, s);
}

nlohmann::json JsonRepo::get_by_id(nlohmann::json root, int id, std::string& name)
{
	for (auto element : root.items())
	{
		if (element.value().contains("ID") && 
			element.value()["ID"].is_number_integer() && 
			element.value()["ID"] == id)
		{
			name = element.key();
			return element.value();
		}
	}
	return nlohmann::json();
}



int JsonRepo::get_int(nlohmann::json root, std::string key, int default_value)
{
	auto it = root.find(key);
	if (it != root.end() && it.value().is_number_integer())
	{
		return it.value().get<json::number_integer_t>();
	}
	return default_value;
}

bool JsonRepo::get_bool(nlohmann::json root, std::string key, bool default_value)
{
	auto it = root.find(key);
	if (it != root.end() && it.value().is_boolean())
	{
		return it.value().get<json::boolean_t>();
	}
	return default_value;
}

float JsonRepo::get_float(nlohmann::json root, std::string key, float default_value)
{
	auto it = root.find(key);
	if (it != root.end() && it.value().is_number_float())
	{
		return it.value().get<json::number_float_t>();
	}
	return default_value;
}

std::string JsonRepo::get_string(nlohmann::json root, std::string key, std::string default_value)
{
	auto it = root.find(key);
	if (it != root.end() && it.value().is_string())
	{
		return it.value().get<json::string_t>();
	}
	return default_value;
}


void JsonRepo::preload()
{
	get_game_settings();
	get_char_data();
	get_item_data();
	get_map_data();
}
