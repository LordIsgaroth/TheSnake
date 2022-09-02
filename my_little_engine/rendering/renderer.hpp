#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>
#include <memory>
#include <unordered_map>

#include "my_little_engine/objects/game_object.hpp"
#include "sprite.hpp"

class Renderer
{
public:
    Renderer(SDL_Window* window);
    std::shared_ptr<Sprite> CreateSprite(std::string path) const;
    void DrawSprite(std::shared_ptr<Sprite> sprite, int x, int y) const;
    void Render() const;
    void AddToRendering(std::shared_ptr<GameObject> gameObject);
    void RemoveFromRendering(int id);
    bool Contains(int id) const;

private:
    SDL_Renderer *sdl_renderer = nullptr;
    static bool initialized;

    std::unordered_map<int, std::shared_ptr<GameObject>> objectsToRender;

    static void Init();
};