#pragma once

#include "my_little_engine.hpp"

struct SnakeHeadSprites
{
    std::shared_ptr<Sprite> headUp = nullptr;
    std::shared_ptr<Sprite> headDown = nullptr;
    std::shared_ptr<Sprite> headRight = nullptr;
    std::shared_ptr<Sprite> headLeft = nullptr;
};

class Snake : public CollisionObject
{
public:
    Snake(std::unique_ptr<SnakeHeadSprites> headSprites);
    void Update(double elapsedTime) override;
    void Input(std::shared_ptr<KeyboardEvent> inputEvent) override;
    void OnCollision(std::shared_ptr<Collision> collision) override;

private:
    double speed = 0.1;
    int dirX = 0;
    int dirY = 0;
    std::unique_ptr<SnakeHeadSprites> headSprites;
};