#pragma once

#include <string>
#include <memory>

#include "texture.hpp"

class TextureRenderer
{
public:
    TextureRenderer(int renderingOrder = 0, bool visible = false);

    bool visible;

    const SDL_Rect& GetRect() const { return *rect; }
    virtual SDL_Texture& GetTexture() const = 0;
    virtual SDL_Surface& GetSurface() const = 0;
    virtual void SetTexture(SDL_Texture* texture) = 0;

    int RenderingOrder() const { return renderingOrder; }

protected:
    std::unique_ptr<SDL_Rect> rect;
    int renderingOrder;

    void CreateRect(int width, int height);
};

class SpriteRenderer : public TextureRenderer
{   
public:    
    SpriteRenderer(std::shared_ptr<Sprite> sprite, int renderingOrder, bool visible = false);
    SpriteRenderer(std::shared_ptr<Sprite> sprite, int width, int height, int renderingOrder, bool visible = false);
    SpriteRenderer(const SpriteRenderer& origin);

    const std::shared_ptr<Sprite> GetSprite() const { return sprite; }

    void SetSprite(std::shared_ptr<Sprite> sprite);

    SDL_Texture& GetTexture() const override;
    SDL_Surface& GetSurface() const override;
    void SetTexture(SDL_Texture* texture) override;

private:
    std::shared_ptr<Sprite> sprite;
};

class LabelRenderer : public TextureRenderer
{
public:
    LabelRenderer(std::unique_ptr<Text> text, int width, int height, int renderingOrder = 100, bool visible = false);

    SDL_Texture& GetTexture() const override;
    SDL_Surface& GetSurface() const override;
    void SetTexture(SDL_Texture* texture) override;

    void SetText(std::string text);

private:
    std::unique_ptr<Text> text;
};