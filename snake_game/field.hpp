#pragma once

#include "my_little_engine/my_little_engine.hpp"
#include "snake_game_objects.hpp"

class Field
{
public:
    Field(Vector2D position, int tileSize, int width, int height);

    const std::vector<std::shared_ptr<GameObject>>& GetFieldTiles() const { return fieldTiles; }
    
    const int Width() const { return width; }
    const int Height() const { return height; }
    const Vector2D& Position() const { return position; }

    void TakePosition(Vector2D position);
    void ReleasePosition(Vector2D position);

    std::vector<Vector2D>& GetFreePositions()
    { 
        return freeTilePositions;
    }
 
private:
    Vector2D position;

    int width;
    int height;
    int tileSize;

    std::vector<std::shared_ptr<GameObject>> fieldTiles;
    
    std::vector<Vector2D> tilePositions;
    std::vector<Vector2D> freeTilePositions;

    std::unique_ptr<SpriteRenderer> CreateTileSpriteRenderer(std::shared_ptr<Sprite> sprite, int renderingOrder);
    
    void CreateGrass();

    void DefineFreePositions();
};