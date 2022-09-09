#include "collision_manager.hpp"

void CollisionManager::AddCollideable(std::shared_ptr<CollisionObject> collideable)
{
    if(Contains(collideable->Id())) return;
    collidableObjects.insert(std::make_pair(collideable->Id(), collideable));
}

void CollisionManager::RemoveCollideable(int id)
{
    if(!Contains(id)) return;
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
        CheckForObject(record.second);
    }
}

void CollisionManager::CheckForObject(std::shared_ptr<CollisionObject> object)
{
    for(auto record : collidableObjects)
    {
        if(record.second != object)
        {
            if(IsColliding(object, record.second))
            {
                object->OnCollision(std::make_shared<Collision>(record.second));
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

    // std::cout << "collision: " << first->CollisionHeight() << " " << first->CollisionWidth() << " " << second->CollisionHeight() << " " << second->CollisionWidth() << std::endl;
    // std::cout << "collision: " << first->posX << " " << first->posY << " " << second->posX << " " << second->posY << std::endl;
    // std::cout << "collision: " << left << " " << right << " " << top << " " << bottom << std::endl;
    // std::cout << std::endl;

    return !(left > 0 || right < 0 || top < 0 || bottom > 0);
}