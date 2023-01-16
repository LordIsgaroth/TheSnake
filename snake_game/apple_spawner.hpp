#pragma once

#include "my_little_engine/my_little_engine.hpp"
#include "snake_game_objects.hpp"

class AppleSpawner
{
public:
    AppleSpawner(int minApplesCount, int tileSize, int appleRenderingOrder);

    void ReduceCurrentApplesCount() { currentApplesCount--; }
    void SpawnApples(std::vector<Vector2D>& freePositions);

private:
    int minApplesCount, currentApplesCount;
    int tileSize;
    int appleRenderingOrder;

    std::shared_ptr<Sprite> appleSprite;
    
    //Change to collection for multiple apples
    const Apple* apple;

    void CreateApple(Vector2D& position);
    Vector2D GetRandomPosition(std::vector<Vector2D>& positions);

};