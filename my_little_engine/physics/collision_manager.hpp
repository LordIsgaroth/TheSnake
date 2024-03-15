#pragma once

#include <memory>
#include <unordered_map>

#include "objects/game_object.hpp"

class CollisionManager
{
public:
    void AddCollideable(std::shared_ptr<CollisionObject> collideable);
    void RemoveCollideable(int id);
    bool Contains(int id) const;
    void CheckCollisions();

private:
    std::unordered_map<int, std::shared_ptr<CollisionObject>> collidableObjects;

    void CheckForObject(std::shared_ptr<CollisionObject>);
    bool IsColliding(std::shared_ptr<CollisionObject> first, std::shared_ptr<CollisionObject> second);
};