#include "../header/JsonUtils.h"

#include <iostream>
#include <fstream>

using json = nlohmann::json;

namespace fs = std::filesystem;

json load_json(std::string filepath)
{
	json j;
	std::ifstream infile(filepath);
	if (!infile.is_open())
	{
		std::cerr << "Failed to open file: " << filepath << std::endl;
		return j;
	}	
	infile >> j;
	return j;
}
