#include "apple.hpp"

//for testing - remove
#include <iostream>

Apple::Apple(std::shared_ptr<Sprite> sprite) : CollisionObject(sprite)
{
    name = "apple";
}

void Apple::OnCollision(std::shared_ptr<Collision> collision)
{
    std::cout << name << " collides with " << collision->Other()->Name() << std::endl;    
}