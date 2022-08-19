#pragma once

#include "my_little_engine.hpp"

#include "snake_game.hpp"

class SnakeGame;

class Apple : public CollisionObject
{
public:
    Apple(std::shared_ptr<Sprite> sprite);
    void OnCollision(std::shared_ptr<Collision> collision) override;

    SnakeGame* game = nullptr;    
    //SnakeGame* game;
};