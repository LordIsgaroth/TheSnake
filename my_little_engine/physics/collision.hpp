#pragma once

#include <memory>
#include "my_little_engine/objects/game_object.hpp"

class GameObject;

class Collision
{
public:
    Collision(std::shared_ptr<GameObject> other);
    std::shared_ptr<GameObject> Other();

private:    
    std::shared_ptr<GameObject> other;
};