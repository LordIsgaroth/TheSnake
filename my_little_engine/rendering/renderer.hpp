#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>
#include <memory>
#include <unordered_map>
#include <map>

#include <iostream>

#include "my_little_engine/objects/game_object.hpp"
#include "sprite.hpp"

class Renderer
{
public:
    Renderer(SDL_Window* window);

    std::shared_ptr<Sprite> CreateSprite(std::string path) const;
    std::shared_ptr<Sprite> CreateSprite(std::string path, int width, int height) const;

    void DrawSprite(const std::unique_ptr<SpriteRenderer>& spriteRenderer, Vector2D position) const;
    void Render() const;
    void AddToRendering(std::shared_ptr<GameObject> gameObject);
    void RemoveFromRendering(int id, int renderingOrder);
    bool ContainsObject(int id, int renderingOrder) const;

private:
    SDL_Renderer *sdl_renderer = nullptr;
    static bool initialized;

    std::multimap<int, std::unordered_map<int, std::shared_ptr<GameObject>>> objectsToRender;

    //std::shared_ptr<Sprite> CreateSpriteFromFile(std::string path, int width, int height);

    bool ContainsOrder(int renderingOrder) const;
    void CreateLayer(int renderingOrder);

    static void Init();
};