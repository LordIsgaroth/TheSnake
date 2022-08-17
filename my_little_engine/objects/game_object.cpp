#include "game_object.hpp"

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