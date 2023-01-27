#pragma once

#include "snake_game_objects.hpp"

class AppleStorage
{
public:
    AppleStorage(int minApplesCount = 1);

    bool CanContainApple();
    void AddApple(std::shared_ptr<Apple> apple);
    void RemoveAppleAtPosition(Vector2D position);
    void RemoveAllApples();

private:
    int minApplesCount;
    std::vector<std::shared_ptr<Apple>> apples;

};