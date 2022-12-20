#include "texture_renderer.hpp"

TextureRenderer::TextureRenderer(int renderingOrder, bool visible)
{
    this->renderingOrder = renderingOrder;
    this->visible = visible;
}

void TextureRenderer::CreateRect(int width, int height)
{
    rect = std::make_unique<SDL_Rect>();
    rect->h = height;
    rect->w = width;
}

SpriteRenderer::SpriteRenderer(std::shared_ptr<Sprite> sprite, int renderingOrder, bool visible) : TextureRenderer(renderingOrder, visible)
{
    this->sprite = sprite;
    CreateRect(sprite->GetSurface().w, sprite->GetSurface().h);
}

SpriteRenderer::SpriteRenderer(std::shared_ptr<Sprite> sprite, int width, int height, int renderingOrder, bool visible) : TextureRenderer(renderingOrder, visible)
{
    this->sprite = sprite;
    CreateRect(width, height);
}

SpriteRenderer::SpriteRenderer(const SpriteRenderer& origin)
{
    this->sprite = origin.GetSprite();
    this->renderingOrder = origin.RenderingOrder();
    this->visible = origin.visible;

    const SDL_Rect& rect = origin.GetRect();
 
    int rectWidth = rect.w;
    int rectHeight = rect.h;

    CreateRect(rectWidth, rectHeight);
}

void SpriteRenderer::SetSprite(std::shared_ptr<Sprite> sprite)
{
    this->sprite = sprite;    
}

SDL_Texture& SpriteRenderer::GetTexture() const
{
    if (!sprite) throw "Sprite do not exist!";
    return sprite->GetTexture();
} 

SDL_Surface& SpriteRenderer::GetSurface() const
{
    if (!sprite) throw "Sprite do not exist!";
    return sprite->GetSurface();
}

void SpriteRenderer::SetTexture(SDL_Texture* texture)
{
    if (!sprite) throw "Sprite do not exist!";
    sprite->SetTexture(texture);
}

LabelRenderer::LabelRenderer(std::unique_ptr<Text> text, int width, int height, int renderingOrder, bool visible) : TextureRenderer(renderingOrder, visible)
{
    this->text = std::move(text);
    CreateRect(width, height);
}

SDL_Texture& LabelRenderer::GetTexture() const
{
    if (!text) throw "Text do not exist!";
    return text->GetTexture();
}

SDL_Surface& LabelRenderer::GetSurface() const
{
    if (!text) throw "Text do not exist!";
    return text->GetSurface();
}

void LabelRenderer::SetTexture(SDL_Texture* texture)
{
    if (!text) throw "Text do not exist!";
    text->SetTexture(texture);
}

void LabelRenderer::SetText(std::string text)
{
    if (!this->text) throw "Text do not exist!";
    this->text->UpdateText(text);
}