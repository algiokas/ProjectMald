#include "..\header\AnimationRepo.h"

std::vector<Animation> Animation::load_animations(std::vector<std::string> asset_subdirs, rapidjson::Value* animations_root, ImageRepo* image_repo)
{
	if (!animations_root->IsObject())
	{
		std::cerr << "load_animations requires JSON value of object type" << std::endl;
		return std::vector<Animation>();
	}

	std::vector<Animation> animations;
	for (rapidjson::Value::ConstMemberIterator it = animations_root->MemberBegin();
		it != animations_root->MemberEnd(); ++it)
	{
		std::string aname = it->name.GetString();

		//TODO handle incomplete animation data
		//TODO update this to use JsonRepo calls rather than raw rapidJson calls
		auto aroot = it->value.GetObject();
		float cyclespeed = aroot["Cyclespeed"].GetFloat();

		Animation new_anim = Animation(aname, cyclespeed);
		auto sprite_names = aroot["Sprites"].GetArray();
		for (auto s_itr = sprite_names.Begin(); s_itr != sprite_names.end(); s_itr++)
		{
			new_anim.frames.push_back(image_repo->loadTexture(asset_subdirs, s_itr->GetString()));
		}
		animations.push_back(new_anim);
	}
	return animations;
}

float Animation::frame_interval()
{
	return BASE_ANIMATION_INTERVAL / cyclespeed;
}

void Animation::advance_frame()
{
	curr_frame_idx = (curr_frame_idx + 1) % (int)frames.size();
}

SDL_Texture* Animation::get_current_frame()
{
	return frames[curr_frame_idx];
}