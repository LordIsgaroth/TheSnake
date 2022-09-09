#pragma once

#include "my_little_engine/my_little_engine.hpp"

class Apple : public CollisionObject
{
public:
    Apple();
    Apple(std::shared_ptr<Sprite> sprite);
};

class Border : public CollisionObject
{
public:
    Border();
    Border(std::shared_ptr<Sprite> sprite); 
};