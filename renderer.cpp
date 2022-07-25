#include "renderer.hpp"
//#include <stdio.h>

bool Renderer::initialized = false;

Renderer::Renderer(GameWindow *gameWindow)
{
    if(!initialized) Init();

    if(!gameWindow->window()) throw "Can not create renderer from null window!";

    sdl_renderer = SDL_CreateRenderer(gameWindow->window(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    if(!sdl_renderer) throw SDL_GetError();

    //SDL_SetRenderDrawColor(sdl_renderer, 0, 0, 0, 0);
}

void Renderer::Init()
{
    int imgFlags = IMG_INIT_PNG;
    if(!(IMG_Init(imgFlags) & imgFlags)) throw IMG_GetError();

    initialized = true;
}

Sprite* Renderer::CreateSprite(std::string path)
{
    SDL_Surface *surface = IMG_Load(path.c_str());
    if(!surface) throw SDL_GetError();

    SDL_Texture *texture = SDL_CreateTextureFromSurface(sdl_renderer, surface);

    if(!texture) throw SDL_GetError();

    return new Sprite(texture, surface->w, surface->h);
}

void Renderer::DrawSprite(Sprite* sprite, int x, int y)
{
    if (!sprite) throw "Sprite do not exist!";

    SDL_Rect rectHead;
    rectHead.h = sprite->Height();
    rectHead.w = sprite->Width();
    rectHead.x = x;
    rectHead.y = y;

    SDL_RenderClear(sdl_renderer);
    // //SDL_RenderCopy(renderer,background,NULL,&background_RECT); //Копируем в рендер фон
    SDL_RenderCopy(sdl_renderer, sprite->Texture(), NULL, &rectHead);
    SDL_RenderPresent(sdl_renderer);
}