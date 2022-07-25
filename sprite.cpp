#include "sprite.hpp"

Sprite::Sprite(SDL_Texture* texture, int width, int height)
{
    this->texture = texture;
    this->width = width;
    this->height = height;
}