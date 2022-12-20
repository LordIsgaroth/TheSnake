#include "texture.hpp"

Texture::~Texture()
{
    delete(surface);
    if(texture != nullptr) SDL_DestroyTexture(texture);
}

Sprite::Sprite(std::string imagePath)
{
    this->imagePath = imagePath;
    CreateSurface();
}

void Sprite::CreateSurface()
{
    surface = IMG_Load(imagePath.c_str());
    if(!surface) throw SDL_GetError();
}

Text::Text(std::string fontPath, int fontSize, std::string text)
{
    font = TTF_OpenFont(fontPath.c_str(), fontSize);

    this->text = text;

    color = {255, 255, 255, 0};
    CreateSurface();
}

Text::~Text()
{
    delete(font);
}

void Text::UpdateText(std::string newText)
{
    this->text = newText;
    SDL_DestroyTexture(texture);
    texture = nullptr;
    CreateSurface();
}

void Text::CreateSurface()
{
    surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if(!surface) throw SDL_GetError();
}