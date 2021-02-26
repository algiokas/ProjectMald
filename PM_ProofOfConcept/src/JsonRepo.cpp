#include "..\header\JsonRepo.h"

#include "rapidjson/filereadstream.h"

#include <cstdio>
#include <string>
#include <iostream>

JsonRepo::~JsonRepo()
{
	//loop over map values and delete the documents by pointer
	std::map<std::string, rapidjson::Document*>::iterator it;
	for (it = GameData.begin(); it != GameData.end(); it++)
	{
		delete it->second;
	}
}

rapidjson::Document* JsonRepo::load_json(std::string filepath)
{
	FILE* fp;
	rapidjson::Document* jdoc = new rapidjson::Document();

	fopen_s(&fp, filepath.c_str(), "rb");
	if (!fp)
	{
		std::cerr << "Failed to open file: " << filepath << " load_json" << std::endl;
		return jdoc;
	}
	char readBuffer[1024];
	rapidjson::FileReadStream file_stream(fp, readBuffer, sizeof(readBuffer));

	jdoc->ParseStream(file_stream);
	fclose(fp);

	return jdoc;
}

rapidjson::Document* JsonRepo::get_game_data(std::string filename)
{
	if (GameData.find(filename) == GameData.end())
	{
		std::string fpath = ASSETS_DIR + filename + JSON_EXT;
		auto jdoc = load_json(fpath);
		if (jdoc->HasParseError())
		{
			std::cerr << "JSON PARSE ERROR: Unable to parse " << fpath << std::endl;
			return NULL;
		}
		GameData.insert(std::make_pair(filename, jdoc));
	}
	return GameData[filename];
}

rapidjson::Document* JsonRepo::get_char_data()
{
	return get_game_data("CharacterData");
}

rapidjson::Document* JsonRepo::get_item_data()
{
	return get_game_data("ItemData");
}

rapidjson::Document* JsonRepo::get_map_data()
{
	return get_game_data("Map");
}



std::string JsonRepo::GetString(Document* doc, std::string key, std::string default_value)
{
	auto it = doc->FindMember(key.c_str());
	if (it != doc->MemberEnd())
		return it->value.GetString();
	return default_value;
}

int JsonRepo::GetInt(Document* doc, std::string key, int default_value)
{
	auto it = doc->FindMember(key.c_str());
	if (it != doc->MemberEnd())
		return it->value.GetInt();
	return default_value;
}

float JsonRepo::GetFloat(Document* doc, std::string key, float default_value)
{
	auto it = doc->FindMember(key.c_str());
	if (it != doc->MemberEnd())
		return it->value.GetFloat();
	return default_value;
}

void JsonRepo::preload()
{
	get_char_data();
	get_item_data();
	get_map_data();
}

//GameDataContainer::GameDataContainer(rapidjson::Document* root)
//{
//	this->root = root;
//}
//
//std::string GameDataContainer::get_string(std::string key)
//{
//	return std::string();
//}
//
//int GameDataContainer::get_int(std::string key)
//{
//	return 0;
//}
//
//float GameDataContainer::get_float(std::string key)
//{
//	return 0.0f;
//}
//
//rapidjson::Document GameDataContainer::get_object(std::string key)
//{
//	if (root->HasMember(key.c_str()))
//	{
//		auto j_object = root->GetObject()
//	}
//	return rapidjson::Document();
//}
//
//T[] GameDataContainer::get_array<T>(std::string key)
//{
//	return rapidjson::Document();
//}
