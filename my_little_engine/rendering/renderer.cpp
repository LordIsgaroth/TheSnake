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

    std::shared_ptr<Sprite> sprite = std::make_shared<Sprite>(std::move(texture), surface->w, surface->h);
    delete(surface);

    return sprite;
}

std::shared_ptr<Sprite> Renderer::CreateSprite(std::string path, int width, int height) const
{
    SDL_Surface *surface = IMG_Load(path.c_str());
    if(!surface) throw SDL_GetError();

    SDL_Texture *texture = SDL_CreateTextureFromSurface(sdl_renderer, surface);

    if(!texture) throw SDL_GetError();

    surface->w = width;
    surface->h = height;

    std::shared_ptr<Sprite> sprite = std::make_shared<Sprite>(std::move(texture), surface->w, surface->h);
    delete(surface);

    return sprite;
}

void Renderer::DrawSprite(const std::unique_ptr<SpriteRenderer>& spriteRenderer, Vector2D position) const
{
    if (!spriteRenderer || !spriteRenderer->GetSprite()) throw "Sprite do not exist!";

    const SDL_Rect* srsRect = &spriteRenderer->GetRect();

    SDL_Rect destRect(spriteRenderer->GetRect());
    destRect.x = position.X();
    destRect.y = position.Y();
    destRect.w = srsRect->w;
    destRect.h = srsRect->h;
    
    SDL_RenderCopy(sdl_renderer, spriteRenderer->GetSprite()->Texture(), &spriteRenderer->GetRect(), &destRect);
}

void Renderer::Render() const
{
    SDL_RenderClear(sdl_renderer);

    for (auto layer : objectsToRender)
    {   
        for (auto record : layer.second)
        {
            DrawSprite(record.second->GetSpriteRenderer(), record.second->position);
        }
    }

    SDL_RenderPresent(sdl_renderer);
}

void Renderer::AddToRendering(std::shared_ptr<GameObject> gameObject)
{
    int renderingOrder = gameObject->GetSpriteRenderer()->RenderingOrder();

    if(ContainsObject(gameObject->Id(), renderingOrder)) return;

    if(!ContainsOrder(renderingOrder)) CreateLayer(renderingOrder);
    objectsToRender.find(renderingOrder)->second.insert(std::make_pair(gameObject->Id(), gameObject));
}

void Renderer::RemoveFromRendering(int id, int renderingOrder)
{
    if(!ContainsObject(id, renderingOrder)) return;

    auto layer = objectsToRender.find(renderingOrder);

    layer->second.erase(id);

    if(layer->second.size() == 0) objectsToRender.erase(renderingOrder);
}

bool Renderer::ContainsObject(int id, int renderingOrder) const
{   
    auto layer = objectsToRender.find(renderingOrder); 

    if(layer == objectsToRender.end()) return false;

    return layer->second.find(id) != layer->second.end();
}

bool Renderer::ContainsOrder(int renderingOrder) const
{
    return objectsToRender.find(renderingOrder) != objectsToRender.end();
}

void Renderer::CreateLayer(int renderingOrder)
{
    std::unordered_map<int, std::shared_ptr<GameObject>> layer;
    objectsToRender.insert(std::make_pair(renderingOrder, layer));
}