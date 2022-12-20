#include "rendering_controller.hpp"

bool RenderingController::initialized = false;

RenderingController::RenderingController(SDL_Window* window)
{
    if(!initialized) Init();

    if(!window) throw "Can not create renderer from null window!";

    sdl_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    if(!sdl_renderer) throw SDL_GetError();

    //SDL_SetRenderDrawColor(sdl_renderer, 0, 0, 0, 0);
}

void RenderingController::Init()
{
    int imgFlags = IMG_INIT_PNG;
    if(!(IMG_Init(imgFlags) & imgFlags)) throw IMG_GetError();

    TTF_Init();

    initialized = true;
}

void RenderingController::DrawTexture(TextureRenderer& textureRenderer, Vector2D position) const
{
    if (!&textureRenderer.GetTexture()) CreateTexture(textureRenderer);
    if (!&textureRenderer.GetTexture()) 
        throw "Texture do not exist!";

    const SDL_Rect* srsRect = &textureRenderer.GetRect();

    SDL_Rect destRect(textureRenderer.GetRect());
    destRect.x = position.X();
    destRect.y = position.Y();
    destRect.w = srsRect->w;
    destRect.h = srsRect->h;
 
    SDL_RenderCopy(sdl_renderer, &textureRenderer.GetTexture(), &textureRenderer.GetRect(), &destRect);
}

void RenderingController::Render() const
{
    SDL_RenderClear(sdl_renderer);

    for (auto layer : objectsToRender)
    {   
        for (auto record : layer.second)
        {
            if(record.second->GetTextureRenderer().visible) DrawTexture(record.second->GetTextureRenderer(), record.second->position);
        }
    }

    SDL_RenderPresent(sdl_renderer);
}

void RenderingController::AddToRendering(std::shared_ptr<GameObject> gameObject)
{
    int renderingOrder = gameObject->GetTextureRenderer().RenderingOrder();

    if(ContainsObject(gameObject->Id(), renderingOrder)) return;

    if(!ContainsOrder(renderingOrder)) CreateLayer(renderingOrder);
    objectsToRender.find(renderingOrder)->second.insert(std::make_pair(gameObject->Id(), gameObject));
}

void RenderingController::RemoveFromRendering(int id, int renderingOrder)
{
    if(!ContainsObject(id, renderingOrder)) return;

    auto layer = objectsToRender.find(renderingOrder);

    layer->second.erase(id);

    if(layer->second.size() == 0) objectsToRender.erase(renderingOrder);
}

bool RenderingController::ContainsObject(int id, int renderingOrder) const
{   
    auto layer = objectsToRender.find(renderingOrder); 

    if(layer == objectsToRender.end()) return false;

    return layer->second.find(id) != layer->second.end();
}

bool RenderingController::ContainsOrder(int renderingOrder) const
{
    return objectsToRender.find(renderingOrder) != objectsToRender.end();
}

void RenderingController::CreateLayer(int renderingOrder)
{
    std::unordered_map<int, std::shared_ptr<GameObject>> layer;
    objectsToRender.insert(std::make_pair(renderingOrder, layer));
}

void RenderingController::CreateTexture(TextureRenderer& textureRenderer) const
{
    SDL_Surface* surface = &textureRenderer.GetSurface();
    SDL_Texture* texture = SDL_CreateTextureFromSurface(sdl_renderer, surface);
    if(!texture) throw SDL_GetError();

    textureRenderer.SetTexture(texture);
}