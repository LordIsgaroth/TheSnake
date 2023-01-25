#include "apple_storage.hpp"

AppleStorage::AppleStorage(int minApplesCount)
{
    this->minApplesCount = minApplesCount;
}

bool AppleStorage::CanContainApple()
{
    return apples.size() < minApplesCount;
}

void AppleStorage::AddApple(std::shared_ptr<Apple> apple)
{ 
    apples.push_back(apple);
    Engine::AddObject(apple);
}

void AppleStorage::RemoveAppleAtPosition(Vector2D position)
{
    auto pos = std::find_if(apples.begin(), apples.end(), [position](std::shared_ptr<Apple> apple) { return apple->position == position; }); 

    if (pos != apples.end())
    {
        Engine::RemoveObject(pos->get()->Id());
        apples.erase(pos);
    }
}

void AppleStorage::RemoveAllApples()
{
    for (std::shared_ptr<Apple> apple : apples)
    {
        Engine::RemoveObject(apple->Id());
    }

    apples.clear();
}