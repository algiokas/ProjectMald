#include "..\header\JsonRepo.h"

#include "rapidjson/filereadstream.h"

#include <cstdio>
#include <string>
#include <iostream>

JsonRepo::~JsonRepo()
{
	//loop over map values and delete the documents by pointer
	std::map<std::string, rapidjson::Document*>::iterator it;
	for (it = json_cache.begin(); it != json_cache.end(); it++)
	{
		delete it->second;
	}
	json_cache.clear();
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
	if (json_cache.find(filename) == json_cache.end())
	{
		//TODO - centralize location of assets directory data
		std::string fpath = ASSETS_DIR + filename + JSON_EXT;
		auto jdoc = load_json(fpath);
		if (jdoc->HasParseError())
		{
			std::cerr << "JSON PARSE ERROR: Unable to parse " << fpath << std::endl;
			return NULL;
		}
		json_cache.insert(std::make_pair(filename, jdoc));
	}
	return json_cache[filename];
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



std::string JsonRepo::GetString(Value* jnode, std::string key, std::string default_value)
{
	auto it = jnode->FindMember(key.c_str());
	if (it != jnode->MemberEnd())
	{
		if (it->value.IsString())
		{
			return it->value.GetString();
		}
		std::cerr << "JSON value [" << key << "] found, but value is not type [string]" << std::endl;
	}
	else
	{
		std::cerr << "JSON value [" << key << "] not found" << std::endl;
	}
	return default_value;
}

int JsonRepo::GetInt(Value* jnode, std::string key, int default_value)
{
	auto it = jnode->FindMember(key.c_str());
	if (it != jnode->MemberEnd())
	{
		if (it->value.IsInt())
		{
			return it->value.GetInt();
		}
		std::cerr << "JSON value [" << key << "] found, but value is not type [int]" << std::endl;
	}
	else
	{
		std::cerr << "JSON value [" << key << "] not found" << std::endl;
	}
	return default_value;
}

float JsonRepo::GetFloat(Value* jnode, std::string key, float default_value)
{
	auto it = jnode->FindMember(key.c_str());
	if (it != jnode->MemberEnd())
	{
		if (it->value.IsFloat())
		{
			return it->value.GetFloat();
		}
		std::cerr << "JSON value [" << key << "] found, but value is not type [float]" << std::endl;
	}
	else
	{
		std::cerr << "JSON value [" << key << "] not found" << std::endl;
	}
	return default_value;
}

Value JsonRepo::GetObject(Value* jnode, std::string key)
{
	auto it = jnode->FindMember(key.c_str());
	if (it != jnode->MemberEnd())
	{
		if (it->value.IsObject())
		{
			return it->value.GetObject();
		}
		std::cerr << "JSON value [" << key << "] found, but value is not type [Object]" << std::endl;
	}
	else
	{
		std::cerr << "JSON value [" << key << "] not found" << std::endl;
	}
	return Value();
}

JArray JsonRepo::GetArray(Value* jnode, std::string key)
{
	auto it = jnode->FindMember(key.c_str());
	if (it != jnode->MemberEnd())
	{
		if (it->value.IsArray())
		{
			return it->value.GetArray();
		}
		std::cerr << "JSON value [" << key << "] found, but value is not type [JArray]" << std::endl;
	}
	else
	{
		std::cerr << "JSON value [" << key << "] not found" << std::endl;
	}
	
	return Value(kArrayType).GetArray();
}


Value JsonRepo::GetById(Value* jnode, int id, std::string* name = NULL)
{
	for (auto it = jnode->Begin(); it != jnode->End(); it++)
	{
		auto sub_it = it->FindMember("ID");
		if (sub_it != it->MemberEnd() && sub_it->value.GetInt() == id) {
			return it->GetObject();
		}			
	}
	std::cerr << "JSON Value with ID = [" << id << "] not found" << std::endl;
	return Value();
}

void JsonRepo::preload()
{
	get_char_data();
	get_item_data();
	get_map_data();
}
