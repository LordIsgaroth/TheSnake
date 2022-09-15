#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <memory>

class Sprite
{
public:
    Sprite(SDL_Texture* texture, int width, int height);
    ~Sprite();
    int Width() { return width; }
    int Height() { return height; }
    SDL_Texture* Texture() { return texture; }
private:
    int width, height;
    SDL_Texture* texture;
};

class SpriteRenderer
{   
public:    
    SpriteRenderer(std::shared_ptr<Sprite> sprite, int renderingOrder);
    SpriteRenderer(std::shared_ptr<Sprite> sprite, int width, int height, int renderingOrder);

    const std::shared_ptr<Sprite> GetSprite() const { return sprite; }  
    const std::unique_ptr<SDL_Rect>& GetRect() const { return rect; }
    int RenderingOrder() const { return renderingOrder; }

    void SetSprite(std::shared_ptr<Sprite> sprite);

private:
    std::shared_ptr<Sprite> sprite;
    std::unique_ptr<SDL_Rect> rect;
    int renderingOrder;

    void CreateRect(int width, int height);
};