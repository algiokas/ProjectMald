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

	//If [root] contains an object with a member named "ID" that's equal to [id]
	nlohmann::json get_by_id(nlohmann::json root, int id);

	//get an object by ID and store the name of the the object in [name]
	nlohmann::json get_by_id(nlohmann::json root, int id, std::string& name);

	//get a data value (non object, non array) from a JSON object by key, if the key doesn't exist, return default value
	static int get_int(nlohmann::json root, std::string key, int default_value);
	static bool get_bool(nlohmann::json root, std::string key, bool default_value);
	static float get_float(nlohmann::json root, std::string key, float default_value);
	static std::string get_string(nlohmann::json root, std::string key, std::string default_str);

	//load all json data in one go rather than on the fly
	void preload();
};