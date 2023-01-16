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
    
    Vector2D newPosition = positions[std::rand() % (positions.size() - 1)];
    
    std::cout << "new apple position (x): " << newPosition.X() << std::endl;
    std::cout << "new apple position (y): " << newPosition.Y() << std::endl;

    return newPosition;
}