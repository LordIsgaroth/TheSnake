#include "game_object.hpp"

int GameObject::maxId;

GameObject::GameObject()
{
    SetId();
}

GameObject::GameObject(std::unique_ptr<SpriteRenderer> spriteRenderer)
{
    SetId();
    this->spriteRenderer = std::move(spriteRenderer);
}

void GameObject::SetId()
{
    id = maxId + 1;
    maxId = id;
}

const Vector2D& GameObject::GetPosition() { return position; }

void GameObject::SetPosition(Vector2D newPostion) { position = newPostion; }

bool GameObject::IsDrawable() { return spriteRenderer != nullptr; }

bool GameObject::HandlesInput() { return handlesInput; }

void GameObject::SetSpriteRenderer(std::unique_ptr<SpriteRenderer> spriteRenderer) { this->spriteRenderer = std::move(spriteRenderer); }

const std::unique_ptr<SpriteRenderer>& GameObject::GetSpriteRenderer() const { return spriteRenderer; }

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

CollisionObject::CollisionObject(std::unique_ptr<SpriteRenderer> spriteRenderer) : GameObject(std::move(spriteRenderer))
{
    borders = std::make_shared<CollisionBorders>();
    borders->width = this->spriteRenderer->GetRect()->w;
    borders->height = this->spriteRenderer->GetRect()->h;
}