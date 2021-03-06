#pragma once

#include <map>
#include <vector>

#include <rapidjson/document.h>

#include "../Global.h"

using namespace rapidjson;


typedef GenericArray<false, Value> JArray;
typedef GenericObject<false, Value> JObject;

//Repo for loading and handling JSON data
//pointers to json data files loaded into memory and frees them on deletion
class JsonRepo
{
	const std::string JSON_EXT = ".json";
	std::map<std::string, Document*> json_cache;

	//read JSON data from file and store it a dynamically allocated rapidJson Document
	//Don't call this without adding pointer to GameData
	Document* load_json(std::string filepath);
	Document* get_game_data(std::string filename);

public:
	~JsonRepo();

	Document* get_game_settings();
	Document* get_char_data();
	Document* get_item_data();
	Document* get_map_data();

	//Check the top level members of [jnode] for a string value with key = [key] 
	static std::string get_string(Value* jnode, std::string key, std::string default_value = "");

	//Check the top level members of [jnode] for an int with key = [key] 
	static int get_int(Value* jnode, std::string key, int default_value = 0);

	//Check the top level members of [jnode] for a float with key = [key] 
	static float get_float(Value* jnode, std::string key, float default_value = 0.0);

	//Check the top level members of [jnode] for a JSON object with key = [key]
	//on failure, returns a rapidJson Value with null type 
	static Value get_jobject(Value* jnode, std::string key);

	//Check the top level members of [jnode] for a JSON object with key = [key]
	//on failure, returns an empty rapidJson array
	static JArray get_jarray(Value* jnode, std::string key);

	//Check the top level members of [jnode] for a JSON container (either object or array)
	//with a member with key "ID" and value = [id]. On failure returns a Value with null type
	static Value get_by_id(Value* jnode, int id, std::string* name = NULL);
	void preload();
};