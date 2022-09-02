#pragma once

#include <memory>
#include <string>

#include "my_little_engine/rendering/sprite.hpp"
#include "my_little_engine/events/input_listener.hpp"
#include "my_little_engine/physics/collision.hpp"

class GameObject : public IInputListener
{
public:
    GameObject();

    virtual void Update(double elapsedTime) {}
    virtual void Input(std::shared_ptr<KeyboardEvent> inputEvent) override {}

    std::string Name() { return name; }
    int Id() { return id; } 

    bool IsDrawable();
    bool HandlesInput();
    void SetSprite(std::shared_ptr<Sprite>);
    std::shared_ptr<Sprite> GetSprite();

    //TODO: make specific class for position
    double posX = 0;
    double posY = 0;

protected:
    static int maxId;

    int id;
    std::string name;
    std::shared_ptr<Sprite> sprite = nullptr;
    bool handlesInput = false;

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
    CollisionObject(int width, int height);
    CollisionObject(std::shared_ptr<Sprite> sprite);
    
    int CollisionWidth() { return borders->width; }
    int CollisionHeight() { return borders->height; }

    virtual void OnCollision(std::shared_ptr<Collision> collision) {}

protected:
    std::shared_ptr<CollisionBorders> borders;  
};