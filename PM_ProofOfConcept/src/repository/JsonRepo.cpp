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


void JsonRepo::preload()
{
	get_game_settings();
	get_char_data();
	get_item_data();
	get_map_data();
}
