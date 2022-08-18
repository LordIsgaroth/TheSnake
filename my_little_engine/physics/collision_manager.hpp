#pragma once

#include <memory>
#include <unordered_set>

#include "../objects/collision_object.hpp"

class CollisionManager
{
public:
    void AddCollideable(std::shared_ptr<CollisionObject> collideable);
    //void RemoveCollideable(std::shared_ptr<CollisionObject> collideable);
    void CheckCollisions();

private:
    std::unordered_set<std::shared_ptr<CollisionObject>> collidableObjects;

    void CheckForObject(std::shared_ptr<CollisionObject>);
    bool IsColliding(std::shared_ptr<CollisionObject> first, std::shared_ptr<CollisionObject> second);
};