#include "renderer.hpp"

bool Renderer::initialized = false;

Renderer::Renderer(SDL_Window* window)
{
    if(!initialized) Init();

    if(!window) throw "Can not create renderer from null window!";

    sdl_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    if(!sdl_renderer) throw SDL_GetError();

    //SDL_SetRenderDrawColor(sdl_renderer, 0, 0, 0, 0);

}

void Renderer::Init()
{
    int imgFlags = IMG_INIT_PNG;
    if(!(IMG_Init(imgFlags) & imgFlags)) throw IMG_GetError();

    initialized = true;
}

std::shared_ptr<Sprite> Renderer::CreateSprite(std::string path) const
{
    SDL_Surface *surface = IMG_Load(path.c_str());
    if(!surface) throw SDL_GetError();

    SDL_Texture *texture = SDL_CreateTextureFromSurface(sdl_renderer, surface);

    if(!texture) throw SDL_GetError();

    return std::make_shared<Sprite>(texture, surface->w, surface->h);
}

void Renderer::DrawSprite(std::shared_ptr<Sprite> sprite, int x, int y) const
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

void Renderer::Render() const
{
    SDL_RenderClear(sdl_renderer);

    for(auto record : objectsToRender)
    {
        DrawSprite(record.second->GetSprite(), record.second->posX, record.second->posY);
    }

    SDL_RenderPresent(sdl_renderer);
}

void Renderer::AddToRendering(std::shared_ptr<GameObject> gameObject)
{
    if(Contains(gameObject->Id())) return;
    objectsToRender.insert(std::make_pair(gameObject->Id(), gameObject));
}

void Renderer::RemoveFromRendering(int id)
{
    if(!Contains(id)) return;
    objectsToRender.erase(id);
}

bool Renderer::Contains(int id) const
{
    if (objectsToRender.find(id) != objectsToRender.end()) return true;
    else return false;
}
