#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "game_window.hpp"
#include "sprite.hpp"

class Renderer
{
public:
    Renderer(GameWindow* gameWindow);
    Sprite* CreateSprite(std::string path);
    void DrawSprite(Sprite* sprite, int x, int y);

private:
    SDL_Renderer *sdl_renderer = nullptr;
    static bool initialized;

    static void Init();
};