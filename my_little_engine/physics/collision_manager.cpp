#include "collision_manager.hpp"

void CollisionManager::AddCollideable(std::shared_ptr<CollisionObject> collideable)
{
    if (Contains(collideable->Id())) return;
    collidableObjects.insert(std::make_pair(collideable->Id(), collideable));
}

void CollisionManager::RemoveCollideable(int id)
{
    if (!Contains(id)) return;
    collidableObjects.erase(id);
}

bool CollisionManager::Contains(int id) const
{
    if (collidableObjects.find(id) != collidableObjects.end()) return true;
    else return false;
}

void CollisionManager::CheckCollisions()
{
    for(auto record : collidableObjects)
    {
        if (record.second->CanCollide()) CheckForObject(record.second);
    }
}

void CollisionManager::CheckForObject(std::shared_ptr<CollisionObject> object)
{
    if (!object->CanCollide()) return;

    for (auto record : collidableObjects)
    {
        if (record.second != object)
        {
            if (record.second->CanCollide() && IsColliding(object, record.second))
            {
                object->OnCollision(std::make_shared<Collision>(record.second));
            }    
        }
    }
}

bool CollisionManager::IsColliding(std::shared_ptr<CollisionObject> first, std::shared_ptr<CollisionObject> second)
{
    const Vector2D firstPosition = first->position;
    const Vector2D secondPosition = second->position;

    double left = secondPosition.X() - (firstPosition.X() + first->CollisionWidth());
    double top = (secondPosition.Y() + second->CollisionHeight()) - firstPosition.Y();
    double right = (secondPosition.X() + second->CollisionWidth()) - firstPosition.X();
    double bottom = secondPosition.Y() - (firstPosition.Y() + first->CollisionHeight());

    return !(left >= 0 || right <= 0 || top <= 0 || bottom >= 0);
}