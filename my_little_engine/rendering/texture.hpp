#pragma once

#include <string>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class Texture
{
public:
    ~Texture();

    SDL_Surface& GetSurface() const { return *surface; }
    SDL_Texture& GetTexture() const { return *texture; }
    void SetTexture(SDL_Texture* texture) { this->texture = texture; }

protected:
    SDL_Surface* surface = nullptr;
    SDL_Texture* texture = nullptr;

    virtual void CreateSurface() = 0;
};

class Sprite : public Texture
{
public:
    Sprite(std::string imagePath);

private:
    std::string imagePath;
    void CreateSurface() override;
};

class Text : public Texture
{
public:
    Text(std::string fontPath, int fontSize, std::string text);
    ~Text();

    void UpdateText(std::string text);

private:
    std::string text;
    TTF_Font* font;
    SDL_Color color;

    void CreateSurface() override;
};