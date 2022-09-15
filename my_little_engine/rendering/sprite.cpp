#include "sprite.hpp"

Sprite::Sprite(SDL_Texture* texture, int width, int height)
{
    this->texture = texture;
    this->width = width;
    this->height = height;
}

Sprite::~Sprite()
{
    delete(texture);
}

SpriteRenderer::SpriteRenderer(std::shared_ptr<Sprite> sprite, int renderingOrder)
{
    this->sprite = sprite;
    this->renderingOrder = renderingOrder;
    CreateRect(sprite->Width(), sprite->Height());
}

SpriteRenderer::SpriteRenderer(std::shared_ptr<Sprite> sprite, int width, int height, int renderingOrder)
{
    this->sprite = sprite;
    this->renderingOrder = renderingOrder;
    CreateRect(width, height);
}

void SpriteRenderer::SetSprite(std::shared_ptr<Sprite> sprite)
{
    this->sprite = sprite;    
}

void SpriteRenderer::CreateRect(int width, int height)
{
    rect = std::make_unique<SDL_Rect>();
    rect->h = height;
    rect->w = width;
}