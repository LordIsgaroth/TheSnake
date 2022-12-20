#pragma once

#include "my_little_engine/my_little_engine.hpp"

class Apple : public CollisionObject
{
public:
    Apple(std::unique_ptr<SpriteRenderer> spriteRenderer);
    void Update(double elapsedTime) override {}
};

class Border : public CollisionObject
{
public:
    Border(std::unique_ptr<SpriteRenderer> spriteRenderer);
    void Update(double elapsedTime) override {} 
};

class Grass : public SceneObject
{
public:
    Grass(std::unique_ptr<SpriteRenderer> spriteRenderer);
    void Update(double elapsedTime) override {}
};