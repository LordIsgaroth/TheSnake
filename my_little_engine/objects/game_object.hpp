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

    std::string Name() { return name; }
    int Id() { return id; } 

    const Vector2D& GetPosition();
    void SetPosition(Vector2D newPosiion);
    
    bool IsDrawable();
    bool HandlesInput();
    void SetSpriteRenderer(std::unique_ptr<SpriteRenderer> spriteRenderer);
    const std::unique_ptr<SpriteRenderer>& GetSpriteRenderer() const;

protected:
    static int maxId;
    int id;

    Vector2D position;

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
    
    int CollisionWidth() { return borders->width; }
    int CollisionHeight() { return borders->height; }
    bool CanCollide() { return canCollide; }

    virtual void OnCollision(std::shared_ptr<Collision> collision) {}

protected:
    bool canCollide;
    std::shared_ptr<CollisionBorders> borders;  
};