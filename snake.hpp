#pragma once

#include "my_little_engine/objects/controllable_object.hpp"

struct SnakeHeadSprites
{
    std::shared_ptr<Sprite> headUp = nullptr;
    std::shared_ptr<Sprite> headDown = nullptr;
    std::shared_ptr<Sprite> headRight = nullptr;
    std::shared_ptr<Sprite> headLeft = nullptr;
};

class Snake : public ControllableObject
{
public:
    Snake(std::unique_ptr<SnakeHeadSprites> headSprites);
    void Update(double elapsedTime) override;
private:
    double speed = 0.1;
    int dirX = 0;
    int dirY = 0;
    std::unique_ptr<SnakeHeadSprites> headSprites;
};