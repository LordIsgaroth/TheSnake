#include "game_object.hpp"

int GameObject::maxId;

GameObject::GameObject()
{
    SetId();
}

void GameObject::SetId()
{
    id = maxId + 1;
    maxId = id;
}

SceneObject::SceneObject(std::unique_ptr<SpriteRenderer> spriteRenderer)
{
    this->spriteRenderer = std::move(spriteRenderer);
}

TextObject::TextObject(std::string labelName, std::unique_ptr<LabelRenderer> labelRenderer)
{
    this->name = labelName;
    this->labelRenderer = std::move(labelRenderer);
}

//void GameObject::SetTextureRenderer(std::unique_ptr<TextureRenderer> textureRenderer) { this->textureRenderer = std::move(textureRenderer); }

// TextureRenderer& GameObject::GetTextureRenderer() const { return *textureRenderer; }


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

CollisionObject::CollisionObject(std::unique_ptr<SpriteRenderer> spriteRenderer) : SceneObject(std::move(spriteRenderer))
{
    borders = std::make_shared<CollisionBorders>();
    borders->width = this->spriteRenderer->GetRect().w;
    borders->height = this->spriteRenderer->GetRect().h;
}

void CollisionObject::SetCollisionBorders(int width, int height)
{
    borders->width = width;
    borders->height = height;
}