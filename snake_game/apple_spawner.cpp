#include "apple_spawner.hpp"

AppleSpawner::AppleSpawner(int tileSize, int appleRenderingOrder)
{
    this->tileSize = tileSize;
    this->appleRenderingOrder = appleRenderingOrder;

    appleSprite = std::make_shared<Sprite>("Graphics/apple.png");
}

std::shared_ptr<Apple> AppleSpawner::SpawnApple(std::vector<Vector2D>& freePositions)
{
    std::unique_ptr<SpriteRenderer> appleSpriteRenderer = std::make_unique<SpriteRenderer>(appleSprite, tileSize, tileSize, appleRenderingOrder, true);

    std::shared_ptr<Apple> newApple = std::make_shared<Apple>(std::move(appleSpriteRenderer));
    newApple->position = GetRandomPosition(freePositions);
    
    return newApple;
}

void AppleSpawner::CreateApple(Vector2D& position)
{
    std::unique_ptr<SpriteRenderer> appleSpriteRenderer = std::make_unique<SpriteRenderer>(appleSprite, tileSize, tileSize, appleRenderingOrder, true);

    std::shared_ptr<Apple> newApple = std::make_shared<Apple>(std::move(appleSpriteRenderer));
    newApple->position = position;
}

Vector2D AppleSpawner::GetRandomPosition(std::vector<Vector2D>& positions)
{
    std::random_device randomDevice;
    std::mt19937 generator(randomDevice());

    std::uniform_int_distribution<> distribution(0, positions.size() - 1);
    int randomNumber = distribution(generator);

    Vector2D newPosition = positions[randomNumber];
    
    return newPosition;
}