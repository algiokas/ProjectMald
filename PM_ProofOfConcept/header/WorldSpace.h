#pragma once

#include <vector>

#include "GameChar.h"
#include "Color.h"
#include "repository/JsonRepo.h"

class GameChar;
class ImageRepo;

class WorldSpace
{
	int width;
	int height;
	int margin;
	float speedmult;
	color bg_color;
	SDL_Texture* bg_texture;	
	std::vector<GameChar*> all_characters;
	GameChar* player_character;
	SDL_Renderer* renderer;

	WorldSpace(int width, int height, int margin, float speedmult, color bg_color, SDL_Texture* bg_texture, SDL_Renderer* renderer) :
		width(width), height(height), margin(margin), speedmult(speedmult), 
		bg_color(bg_color), bg_texture(bg_texture), renderer(renderer), player_character(NULL) {}

	//Used to check if a rectangle collides with the worldspace itself
	bool world_collision_x(float x1, float x2);
	bool world_collision_y(float y1, float y2);

	bool object_collision()

public:
	~WorldSpace();

	static WorldSpace* CreateWorld(JsonRepo* json_repo, ImageRepo* img_repo, SDL_Renderer* renderer);

	bool check_collision(GameChar* c);
	GameChar* get_pc();
	void add_character(GameChar* new_char);
	void update();
	void render();
};