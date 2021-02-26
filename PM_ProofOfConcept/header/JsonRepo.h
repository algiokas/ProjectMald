#pragma once

#include <map>
#include <string>
#include <vector>

#include <rapidjson/document.h>

using namespace rapidjson;

const std::string ASSETS_DIR = "assets/";
const std::string JSON_EXT = ".json";

typedef GenericArray<false, Value> JArray;

class JsonRepo
{
	std::map<std::string, Document*> GameData;
	Document* load_json(std::string filepath);
	Document* get_game_data(std::string filename);
public:
	~JsonRepo();
	Document* get_char_data();
	Document* get_item_data();
	Document* get_map_data();

	static std::string GetString(Value* jnode, std::string key, std::string default_value = "");
	static int GetInt(Value* jnode, std::string key, int default_value = 0);
	static float GetFloat(Value* jnode, std::string key, float default_value = 0.0);
	static Value* GetObject(Value* jnode, std::string key);
	static JArray* GetArray(Value* jnode, std::string key);
	static Value* GetById(Value* jnode, int id);
	void preload();
};



//class GameDataContainer
//{
//	Document* root;
//public:
//	GameDataContainer(Document* root);
//	std::string get_string(std::string key);
//	int get_int(std::string key);
//	float get_float(std::string key);
//	Document get_object(std::string key);
//	template <typename T, int N> std::array<T, N> get_array(std::string key);
//};