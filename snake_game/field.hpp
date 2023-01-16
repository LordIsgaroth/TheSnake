#pragma once

#include "my_little_engine/my_little_engine.hpp"
#include "snake_game_objects.hpp"

class Field
{
public:
    Field(Vector2D position, int tileSize, int width, int height);

    const std::vector<std::shared_ptr<GameObject>>& GetFieldTiles() const { return fieldTiles; }
    const std::vector<std::shared_ptr<Border>>& GetBorderTiles() const { return borderTiles; }

    Vector2D GetRandomFreePosition();
    std::vector<Vector2D>& GetFreePositions()
    {
        DefineFreePositions(); 
        return freeTilePositions;
    }

    //void TakePosition(Vector2D position);
    //void ReleasePosition(Vector2D position);

private:
    Vector2D position;

    int width;
    int height;
    int tileSize;

    std::vector<std::shared_ptr<GameObject>> fieldTiles;
    std::vector<std::shared_ptr<Border>> borderTiles;

    std::vector<Vector2D> tilePositions;
    std::vector<Vector2D> freeTilePositions;

    std::unique_ptr<SpriteRenderer> CreateTileSpriteRenderer(std::shared_ptr<Sprite> sprite, int renderingOrder);
    
    void CreateGrass();    
    void CreateBorders();

    void DefineFreePositions();
};