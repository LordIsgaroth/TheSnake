#include "snake_game_objects.hpp"

Apple::Apple()
{
    name = "Apple";
}

Apple::Apple(std::shared_ptr<Sprite> sprite) : CollisionObject(sprite)
{
    name = "Apple";
}

Border::Border()
{
    name = "Border";
}

Border::Border(std::shared_ptr<Sprite> sprite) : CollisionObject(sprite)
{
    name = "Border";
}