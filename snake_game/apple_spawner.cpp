#include "apple_spawner.hpp"

AppleSpawner::AppleSpawner(int minApplesCount, int tileSize, int appleRenderingOrder)
{
    this->minApplesCount = minApplesCount;
    this->tileSize = tileSize;
    this->appleRenderingOrder = appleRenderingOrder;
    currentApplesCount = 0;

    appleSprite = std::make_shared<Sprite>("Graphics/apple.png");
}

void AppleSpawner::SpawnApples(std::vector<Vector2D>& freePositions)
{

    while(currentApplesCount < minApplesCount)
    {
        Vector2D position = GetRandomPosition(freePositions);
        CreateApple(position);
        AppleSpawned(position);
    }
}

void AppleSpawner::CreateApple(Vector2D& position)
{
    std::unique_ptr<SpriteRenderer> appleSpriteRenderer = std::make_unique<SpriteRenderer>(appleSprite, tileSize, tileSize, appleRenderingOrder, true);

    std::shared_ptr<Apple> newApple = std::make_shared<Apple>(std::move(appleSpriteRenderer));
    newApple->position = position;
    
    //change to push into collection
    apple = newApple.get();

    currentApplesCount++;

    Engine::AddObject(newApple);
}

Vector2D AppleSpawner::GetRandomPosition(std::vector<Vector2D>& positions)
{
    std::srand(std::time(nullptr));

    int randomNumber = std::rand() % (positions.size() - 1);
    Vector2D newPosition = positions[randomNumber];
    
    return newPosition;
}