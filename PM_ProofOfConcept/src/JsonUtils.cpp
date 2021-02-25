#include "../header/JsonUtils.h"

#include "rapidjson/filereadstream.h"

#include <cstdio>
#include <string>
#include <iostream>

using namespace rapidjson;

Document load_json(std::string filepath)
{
	FILE* fp;
	Document jdoc;

	fopen_s(&fp, filepath.c_str(), "rb");
	if (!fp)
	{
		std::cerr << "Failed to open file: " << filepath << " load_json" << std::endl;
		return jdoc;
	}
	char readBuffer[1024];
	FileReadStream file_stream(fp, readBuffer, sizeof(readBuffer));

	jdoc.ParseStream(file_stream);
	fclose(fp);

	return jdoc;	
}
