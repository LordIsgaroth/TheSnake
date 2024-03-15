#pragma once

#include <memory>
#include <string>

#include "rendering/texture_renderer.hpp"
#include "events/input_listener.hpp"
#include "physics/collision.hpp"
#include "common/vector.hpp"

class GameObject : public IInputListener
{
public:
    GameObject();

    virtual void Update(double elapsedTime) = 0;
    virtual void Input(std::shared_ptr<SDL_Event> inputEvent) override {}

    std::string Name() const { return name; }
    int Id() const { return id; } 

    Vector2D position;
    
    bool HandlesInput() const { return handlesInput; }
    virtual bool IsDrawable() const = 0;
    virtual TextureRenderer& GetTextureRenderer() const = 0;

protected:
    int id;    
    std::string name;
    bool handlesInput = false;

private:
    static int maxId;
    void SetId();
};

class SceneObject : public GameObject
{
public:
    SceneObject() {}
    SceneObject(std::unique_ptr<SpriteRenderer> spriteRenderer);

    bool IsDrawable() const override { return spriteRenderer != nullptr; }
    TextureRenderer& GetTextureRenderer() const override { return *spriteRenderer; }
    SpriteRenderer& GetSpriteRenderer() const { return *spriteRenderer; }

protected:
    std::unique_ptr<SpriteRenderer> spriteRenderer;
};

class TextObject : public GameObject
{
public:
    TextObject(std::string labelName, std::unique_ptr<LabelRenderer> labelRenderer);

    void SetText(std::string text) { labelRenderer->SetText(text); } 

    void Update(double elapsedTime) override {}
    bool IsDrawable() const override { return labelRenderer != nullptr; }
    TextureRenderer& GetTextureRenderer() const override { return *labelRenderer; }
    
protected:
    std::unique_ptr<LabelRenderer> labelRenderer;
};

struct CollisionBorders
{
    int width;
    int height;
};

class Collision;

class CollisionObject : public SceneObject
{  
public:
    CollisionObject();
    CollisionObject(std::unique_ptr<SpriteRenderer> spriteRenderer);
    CollisionObject(int width, int height);
    
    void SetCollisionBorders(int width, int height);
    int CollisionWidth() const { return borders->width; }
    int CollisionHeight() const { return borders->height; }
    bool CanCollide() const { return canCollide; }

    virtual void OnCollision(std::shared_ptr<Collision> collision) {}

protected:
    bool canCollide;
    std::shared_ptr<CollisionBorders> borders;  
};