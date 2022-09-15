#include "snake_game_objects.hpp"

Apple::Apple(std::unique_ptr<SpriteRenderer> spriteRenderer) : CollisionObject(std::move(spriteRenderer))
{
    name = "Apple";
    canCollide = true;
}

Border::Border(std::unique_ptr<SpriteRenderer> spriteRenderer) : CollisionObject(std::move(spriteRenderer))
{
    name = "Border";
    canCollide = true;
}

Grass::Grass(std::unique_ptr<SpriteRenderer> spriteRenderer) : GameObject(std::move(spriteRenderer))
{
    name = "Grass";
}