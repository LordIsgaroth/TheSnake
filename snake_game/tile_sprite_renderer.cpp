#include "tile_sprite_renderer.hpp"

TileSpriteRenderer::TileSpriteRenderer(std::shared_ptr<Sprite> sprite, int tileSize, int renderingOrder, bool visible) 
    : SpriteRenderer(sprite, tileSize, tileSize, renderingOrder, visible)
{}