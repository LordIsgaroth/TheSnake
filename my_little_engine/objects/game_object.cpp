#include "game_object.hpp"

int GameObject::maxId;

GameObject::GameObject()
{
    id = maxId + 1;
    maxId = id;
}

bool GameObject::IsDrawable()
{
    return sprite != nullptr;
}

bool GameObject::HandlesInput()
{
    return handlesInput;
}

void GameObject::SetSprite(std::shared_ptr<Sprite> sprite)
{
    this->sprite = sprite;
}

std::shared_ptr<Sprite> GameObject::GetSprite()
{
    return sprite;
}

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