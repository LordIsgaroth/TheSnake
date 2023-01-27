#pragma once

#include "my_little_engine/my_little_engine.hpp"

class TileSpriteRenderer : public SpriteRenderer
{
public:
    TileSpriteRenderer(std::shared_ptr<Sprite> sprite, int tileSize, int renderingOrder, bool visible = false);
};