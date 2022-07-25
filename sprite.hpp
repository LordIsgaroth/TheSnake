#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

class Sprite
{
public:
    Sprite(SDL_Texture* texture, int width, int height);
    int Width() { return width; }
    int Height() { return height; }
    SDL_Texture* Texture() { return texture; }
private:
    int width, height;
    SDL_Texture* texture;
};