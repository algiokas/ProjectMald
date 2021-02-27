#include "../header/Game.h"
#include "../header/Color.h"

#include <iostream>

#include <SDL2/SDL_image.h>

//TODO - move game settings to its own repo with caching
struct gamesettings
{
    std::string window_name;
    int window_width;
    int window_height;
};

gamesettings load_settings(JsonRepo* json_repo)
{
    gamesettings settings;

    Document* settings_doc = json_repo->get_game_settings();
    settings.window_name = json_repo->get_string(settings_doc, "Window_Name", "[DEFAULT WINDOW NAME]");
    settings.window_width = json_repo->get_int(settings_doc, "Window_Width", 640);
    settings.window_height = json_repo->get_int(settings_doc, "Window_Height", 480);
    
    return settings;
}


bool init_game(SDL_Window*& window, SDL_Renderer*& renderer, ImageRepo*& img_repo, JsonRepo*& json_repo, WorldSpace*& world)
{
    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    json_repo = new JsonRepo();
    gamesettings settings = load_settings(json_repo);

    //Create a window
    window = SDL_CreateWindow(settings.window_name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
                            settings.window_width, settings.window_height, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    //Get renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    img_repo = new ImageRepo(renderer);
    if (!img_repo->img_init_success) {
        return false;
    }

    world = WorldSpace::CreateWorld(json_repo, img_repo, renderer);

    return true;
}

void close(SDL_Window* window, WorldSpace* world)
{
    delete world; //MWAHAHAHA

    SDL_DestroyWindow(window);
    window = NULL;

    IMG_Quit();
    SDL_Quit();
}
