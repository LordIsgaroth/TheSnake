#pragma once

#include <random>

#include "my_little_engine.hpp"
#include "snake_game_objects.hpp"

class AppleSpawner
{
public:
    AppleSpawner(int tileSize, int appleRenderingOrder);
    std::shared_ptr<Apple> SpawnApple(std::vector<Vector2D>& freePositions);

private:
    int tileSize;
    int appleRenderingOrder;

    std::shared_ptr<Sprite> appleSprite;

    void CreateApple(Vector2D& position);
    Vector2D GetRandomPosition(std::vector<Vector2D>& positions);
};