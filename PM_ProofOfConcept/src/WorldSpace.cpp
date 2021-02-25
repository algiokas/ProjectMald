#include "../header/WorldSpace.h"
#include "../header/JsonUtils.h"

WorldSpace::WorldSpace(int width, int height, int margin, ImageRepo* img_repo, SDL_Renderer* renderer)
{
	this->width = width;
	this->height = height;
	this->margin = margin;
	this->bg_color = COLOR_BLACK; // default background color
	this->img_repo = img_repo;
	this->renderer = renderer;

	init();
}

WorldSpace::~WorldSpace()
{
	for (GameChar* c : all_characters)
	{
		delete c;
	}
}

void WorldSpace::init()
{
	auto worldData = load_json("assets/Map.json");
	if (worldData.HasMember("backgroundimage"))
	{
		std::string fname = worldData["backgroundimage"].GetString();
		bg_texture = img_repo->loadTexture("Background/" + fname);
	}
	//Set background color, this is the color that displays behind the background image 
	//and will show through if the background has any transparency
	SDL_SetRenderDrawColor(renderer, COLOR_BLACK.r, COLOR_BLACK.g, COLOR_BLACK.b, 0xFF);
}

bool WorldSpace::check_collision_x(float x1, float x2)
{
	return (x1 < margin && x2 >= width - margin);
}

bool WorldSpace::check_collision_y(float y1, float y2)
{
	return (y1 < margin && y2 >= height - margin);
}

void WorldSpace::add_character(GameChar* new_char)
{
	all_characters.push_back(new_char);

	if (all_characters.size() == 1) {
		player_character = all_characters[0];
	}
}

void WorldSpace::render()
{
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, bg_texture, NULL, NULL);

	for (GameChar* c : all_characters)
	{
		c->render(renderer);
	}	
	SDL_RenderPresent(renderer);
}
