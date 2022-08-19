#include "renderer.hpp"
//#include <stdio.h>

bool Renderer::initialized = false;

Renderer::Renderer(std::shared_ptr<GameWindow> gameWindow)
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

std::shared_ptr<Sprite> Renderer::CreateSprite(std::string path)
{
    SDL_Surface *surface = IMG_Load(path.c_str());
    if(!surface) throw SDL_GetError();

    SDL_Texture *texture = SDL_CreateTextureFromSurface(sdl_renderer, surface);

    if(!texture) throw SDL_GetError();

    return std::make_shared<Sprite>(texture, surface->w, surface->h);
}

void Renderer::DrawSprite(std::shared_ptr<Sprite> sprite, int x, int y)
{
    if (!sprite) throw "Sprite do not exist!";

    // SDL_Rect rect;
    // rect.h = sprite->Height();
    // rect.w = sprite->Width();
    sprite->Rect()->x = x;
    sprite->Rect()->y = y;

    // //SDL_RenderCopy(renderer,background,NULL,&background_RECT); //Копируем в рендер фон
    SDL_RenderCopy(sdl_renderer, sprite->Texture(), NULL, sprite->Rect());
}

void Renderer::Render()
{
    SDL_RenderClear(sdl_renderer);

    for(std::shared_ptr<GameObject> gameObject : objectsToRender)
    {
        DrawSprite(gameObject->GetSprite(), gameObject->posX, gameObject->posY);
    }

    SDL_RenderPresent(sdl_renderer);
}

void Renderer::AddToRendering(std::shared_ptr<GameObject> gameObject)
{
    auto objInSet = objectsToRender.find(gameObject);

    if (objInSet == objectsToRender.end())
    {
        objectsToRender.insert(gameObject);
    }   
}

void Renderer::RemoveFromRendering(std::shared_ptr<GameObject> gameObject)
{
    auto objInSet = objectsToRender.find(gameObject);

    if (objInSet != objectsToRender.end())
    {
        objectsToRender.erase(*objInSet);
    }
}