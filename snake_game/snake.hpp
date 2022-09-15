#pragma once

#include "my_little_engine/my_little_engine.hpp"

#include "snake_event.hpp"

struct SnakeHeadSprites
{
    std::shared_ptr<Sprite> headUp = nullptr;
    std::shared_ptr<Sprite> headDown = nullptr;
    std::shared_ptr<Sprite> headRight = nullptr;
    std::shared_ptr<Sprite> headLeft = nullptr;
};

class Snake : public CollisionObject, public ISubject<std::shared_ptr<SnakeEvent>>
{
public:
    Snake(std::unique_ptr<SpriteRenderer> spriteRenderer, std::unique_ptr<SnakeHeadSprites> headSprites);
    void Update(double elapsedTime) override;
    void Input(std::shared_ptr<KeyboardEvent> inputEvent) override;
    void OnCollision(std::shared_ptr<Collision> collision) override;

    void Attach(std::shared_ptr<IObserver<std::shared_ptr<SnakeEvent>>> observer) override;
    void Detach(std::shared_ptr<IObserver<std::shared_ptr<SnakeEvent>>> observer) override;
    void Notify(std::shared_ptr<SnakeEvent> message) override;

private:
    bool alive;
    double speed = 0.2;
    
    Vector2D direction, nextDirection;

    std::unique_ptr<SnakeHeadSprites> headSprites;

    std::shared_ptr<IObserver<std::shared_ptr<SnakeEvent>>> observer;
};