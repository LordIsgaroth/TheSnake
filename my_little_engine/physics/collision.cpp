#include "collision.hpp"

Collision::Collision(std::shared_ptr<GameObject> other)
{
    this->other = other;
}

std::shared_ptr<GameObject> Collision::Other()
{
    return other;
}