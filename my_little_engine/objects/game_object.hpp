#pragma once

#include <memory>
#include <string>

#include "my_little_engine/rendering/sprite.hpp"
#include "my_little_engine/events/input_listener.hpp"
#include "my_little_engine/physics/collision.hpp"
#include "my_little_engine/common/vector.hpp"

class GameObject : public IInputListener
{
public:
    GameObject();
    GameObject(std::unique_ptr<SpriteRenderer> spriteRenderer);    

    virtual void Update(double elapsedTime) = 0;
    virtual void Input(std::shared_ptr<KeyboardEvent> inputEvent) override {}

    std::string Name() const { return name; }
    int Id() const { return id; } 

    Vector2D position;
    
    bool HandlesInput() const { return handlesInput; }
    bool IsDrawable() const { return spriteRenderer != nullptr; }
    void SetSpriteRenderer(std::unique_ptr<SpriteRenderer> spriteRenderer);
    const std::unique_ptr<SpriteRenderer>& GetSpriteRenderer() const;

protected:
    static int maxId;
    int id;
    
    std::string name;
    std::unique_ptr<SpriteRenderer> spriteRenderer = nullptr;
    bool handlesInput = false;

    void SetId();
};

struct CollisionBorders
{
    int width;
    int height;
};

class Collision;

class CollisionObject : public GameObject
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