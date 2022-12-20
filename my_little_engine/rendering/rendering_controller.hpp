#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>
#include <memory>
#include <unordered_map>
#include <map>
#include <typeinfo>

#include <iostream>

#include "texture.hpp"
#include "texture_renderer.hpp"
#include "my_little_engine/objects/game_object.hpp"

class RenderingController
{
public:
    RenderingController(SDL_Window* window);

    void Render() const;
    void AddToRendering(std::shared_ptr<GameObject> gameObject);
    void RemoveFromRendering(int id, int renderingOrder);
    bool ContainsObject(int id, int renderingOrder) const;

private:
    SDL_Renderer* sdl_renderer = nullptr;
    static bool initialized;

    std::multimap<int, std::unordered_map<int, std::shared_ptr<GameObject>>> objectsToRender;

    void CreateTexture(TextureRenderer& textureRenderer) const;
    void DrawTexture(TextureRenderer& textureRenderer, Vector2D position) const;

    bool ContainsOrder(int renderingOrder) const;
    void CreateLayer(int renderingOrder);

    static void Init();
};