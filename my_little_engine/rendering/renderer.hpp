#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>
#include <memory>
#include <unordered_set>

#include "../game_window.hpp"
#include "../objects/game_object.hpp"
#include "sprite.hpp"

class Renderer
{
public:
    Renderer(std::shared_ptr<GameWindow> gameWindow);
    std::shared_ptr<Sprite> CreateSprite(std::string path);
    void DrawSprite(std::shared_ptr<Sprite> sprite, int x, int y);
    void Render();
    void AddToRendering(std::shared_ptr<GameObject> gameObject);
    void RemoveFromRendering(std::shared_ptr<GameObject> gameObject);

private:
    SDL_Renderer *sdl_renderer = nullptr;
    static bool initialized;

    std::unordered_set<std::shared_ptr<GameObject>> objectsToRender;

    static void Init();
};