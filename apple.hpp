#pragma once

#include "my_little_engine.hpp"

class Apple : public CollisionObject
{
public:
    Apple(std::shared_ptr<Sprite> sprite);
    void OnCollision(std::shared_ptr<Collision> collision) override;
};