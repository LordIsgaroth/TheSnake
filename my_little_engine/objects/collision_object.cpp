#include "collision_object.hpp"

CollisionObject::CollisionObject()
{
    borders = std::make_shared<CollisionBorders>();
    borders->width = 0;
    borders->height = 0;
}

CollisionObject::CollisionObject(int width, int height)
{
    borders = std::make_shared<CollisionBorders>();
    borders->width = width;
    borders->height = height;
};

CollisionObject::CollisionObject(std::shared_ptr<Sprite> sprite)
{
    SetSprite(sprite);

    borders = std::make_shared<CollisionBorders>();
    borders->width = sprite->Width();
    borders->height = sprite->Height();
}