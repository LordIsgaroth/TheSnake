#pragma once

#include <memory>

#include "game_object.hpp"
#include "../physics/collision.hpp"
#include "../common/ISubject.hpp"

struct CollisionBorders
{
    int width;
    int height;
};

class CollisionObject : public GameObject
{  
public:
    CollisionObject();
    CollisionObject(int width, int height);
    CollisionObject(std::shared_ptr<Sprite> sprite);
    
    int CollisionWidth() { return borders->width; }
    int CollisionHeight() { return borders->height; }

    virtual void OnCollision(std::shared_ptr<Collision> collision) {}

protected:
    std::shared_ptr<CollisionBorders> borders;  
};