#pragma once

#include <vector>

#include "GameChar.h"
#include "Color.h"

class GameChar;
class ImageRepo;

class WorldSpace
{
	int width;
	int height;
	int margin;
	std::vector<GameChar*> all_characters;
	GameChar* player_character;
	color bg_color;
	SDL_Texture* bg_texture;
	ImageRepo* img_repo;
	SDL_Renderer* renderer;

	void init();
public:
	WorldSpace(int width, int height, int margin, ImageRepo* img_repo, SDL_Renderer* renderer);
	~WorldSpace();
	bool check_collision_x(float x1, float x2);
	bool check_collision_y(float y1, float y2);
	void add_character(GameChar* new_char);
	void render();
};