#include "..\header\Animation.h"


float Animation::frame_interval()
{
	return BASE_ANIMATION_INTERVAL / cyclespeed;
}

void Animation::advance_frame()
{
	curr_frame_idx = (curr_frame_idx + 1) % (int)frames.size();
}

SDL_Texture* Animation::current_frame()
{
	return frames[curr_frame_idx];
}

using json = nlohmann::json;

std::map<std::string, Animation> Animation::load_animations(std::vector<std::string> asset_subdirs, json animations_root, ImageRepo* image_repo)
{
	if (!animations_root.is_object())
	{
		std::cerr << "load_animations() requires JSON value of object type" << std::endl;
		//return std::map<std::string, Animation>();
	}
	std::map<std::string, Animation> animations;
	try
	{
		for (auto& element : animations_root.items())
		{
			std::string aname = element.key();
			json aroot = element.value();
			float cyclespeed = aroot.at("Cyclespeed");
			if (aroot.contains("Directions"))
			{
				for (auto& direction : aroot.at("Directions").items())
				{
					std::string anim_key;
					if (cardinal_values.count(direction.key()) > 0)
					{
						cardinaldir dir = cardinal_values.at(direction.key());
						anim_key = get_key(aname, dir);
						Animation new_anim = Animation(aname, cyclespeed, dir);
						for (json::string_t sprite_name : direction.value())
						{
							new_anim.frames.push_back(image_repo->loadTexture(asset_subdirs, sprite_name));
						}
						animations.insert(std::make_pair(anim_key, new_anim));
					}
				}
			}
			else
			{
				Animation new_anim = Animation(aname, cyclespeed);
				for (json::string_t sprite_name : aroot.at("Sprites"))
				{
					new_anim.frames.push_back(image_repo->loadTexture(asset_subdirs, sprite_name));
				}
				animations.insert(std::make_pair(aname, new_anim));
			}
		}
	}
	catch (json::exception ex)
	{
		std::cerr << "load_animations() JSON error : " << ex.what() << std::endl;
	}
	return animations;
}

std::string Animation::get_key(std::string aname, cardinaldir dir)
{
	if (dir == cardinaldir::NODIR)
		return aname;

	return aname + "-" + cardinal_names.at(dir);
}




