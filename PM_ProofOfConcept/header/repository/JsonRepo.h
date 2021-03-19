#pragma once

#include <map>
#include <vector>
#include <memory>

#include <nlohmann/json.hpp>

#include "../Global.h"


//Repo for loading and handling JSON data
//stores pointers to all loaded json objects
class JsonRepo
{	
	std::map<std::string, std::unique_ptr<nlohmann::json>> json_cache;

	//read JSON data from file and store it a dynamically allocated json object
	std::unique_ptr<nlohmann::json> load_json(std::string filepath);
	nlohmann::json get_game_data(std::string filename);

public:
	~JsonRepo();

	nlohmann::json get_game_settings();
	nlohmann::json get_char_data();
	nlohmann::json get_item_data();
	nlohmann::json get_map_data();

	//load all json data in one go rather than on the fly
	void preload();
};