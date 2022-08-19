#include "collision_manager.hpp"

void CollisionManager::AddCollideable(std::shared_ptr<CollisionObject> collideable)
{
    auto objInSet = collidableObjects.find(collideable);

    if (objInSet == collidableObjects.end())
    {
        collidableObjects.insert(collideable);
    }
}

void CollisionManager::RemoveCollideable(std::shared_ptr<CollisionObject> collideable)
{
    auto objInSet = collidableObjects.find(collideable);

    if (objInSet != collidableObjects.end())
    {
        collidableObjects.erase(*objInSet);
    }
}

void CollisionManager::CheckCollisions()
{
    for(std::shared_ptr<CollisionObject> object : collidableObjects)
    {
        CheckForObject(object);
    }
}

void CollisionManager::CheckForObject(std::shared_ptr<CollisionObject> object)
{
    for(std::shared_ptr<CollisionObject> other : collidableObjects)
    {
        if(other != object)
        {
            if(IsColliding(object, other))
            {
                object->OnCollision(std::make_shared<Collision>(other));
            }    
        }
    }
}

bool CollisionManager::IsColliding(std::shared_ptr<CollisionObject> first, std::shared_ptr<CollisionObject> second)
{
    double left = second->posX - (first->posX + first->CollisionWidth());
    double top = (second->posY + second->CollisionHeight()) - first->posY;
    double right = (second->posX + second->CollisionWidth()) - first->posX;
    double bottom = second->posY - (first->posY + first->CollisionHeight());

    return !(left > 0 || right < 0 || top < 0 || bottom > 0);
}