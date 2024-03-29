#include "field.hpp"
#include "snake_game_objects.hpp"

Field::Field(Vector2D position, int tileSize, int width, int height)
{
    this->position = position;
    this->tileSize = tileSize;
    this->width = width;
    this->height = height;

    CreateGrass();
    ReleaseAllPositions();
}

void Field::CreateGrass()
{
    std::shared_ptr<Sprite> grassSprite = std::make_shared<Sprite>("Graphics/grass.png");

    for (int i = 0; i < width * height; i++)
    {
        std::shared_ptr<Grass> grass = std::make_shared<Grass>(CreateTileSpriteRenderer(grassSprite, 0));
        int x = tileSize + (i % width) * tileSize;
        int y = position.Y() + tileSize + (i / width) * tileSize;

        grass->position = Vector2D(x, y);

        tilePositions.push_back(grass->position);
        fieldTiles.push_back(grass);
    }
}
void Field::ReleaseAllPositions()
{
    freeTilePositions.clear();

    for (Vector2D position : tilePositions)
    { 
        freeTilePositions.push_back(position);
    }
}

std::unique_ptr<SpriteRenderer> Field::CreateTileSpriteRenderer(std::shared_ptr<Sprite> sprite, int renderingOrder)
{
    return std::move(std::make_unique<SpriteRenderer>(sprite, tileSize, tileSize, renderingOrder, true));
}

void Field::TakePosition(Vector2D position)
{
    auto pos = std::find_if(freeTilePositions.begin(), freeTilePositions.end(), [position](const Vector2D& freePosition) { return freePosition == position; } ); 

    if (pos != freeTilePositions.end())
    {
        freeTilePositions.erase(pos);
    }
}

void Field::ReleasePosition(Vector2D position)
{
    auto pos = std::find_if(freeTilePositions.begin(), freeTilePositions.end(), [position](const Vector2D& freePosition) { return freePosition == position; } );

    if (pos == freeTilePositions.end())
    {
        freeTilePositions.push_back(position);
    }
}