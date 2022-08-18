#pragma once

#include <memory>
#include "../objects/game_object.hpp"

class Collision
{
public:
    Collision(std::shared_ptr<GameObject> other);
    std::shared_ptr<GameObject> Other();

private:    
    std::shared_ptr<GameObject> other;
};