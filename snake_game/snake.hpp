#pragma once

#include "my_little_engine/my_little_engine.hpp"

#include "snake_event.hpp"
#include "snake_game_objects.hpp"

struct SnakeHeadSprites
{
    std::shared_ptr<Sprite> headUp = nullptr;
    std::shared_ptr<Sprite> headDown = nullptr;
    std::shared_ptr<Sprite> headRight = nullptr;
    std::shared_ptr<Sprite> headLeft = nullptr;
};

struct SnakeSegmentSprites
{
    std::shared_ptr<Sprite> bodyBottomLeft = nullptr;
    std::shared_ptr<Sprite> bodyBottomRight = nullptr;
    std::shared_ptr<Sprite> bodyTopLeft = nullptr;
    std::shared_ptr<Sprite> bodyTopRight = nullptr;
    std::shared_ptr<Sprite> bodyHorizontal = nullptr;
    std::shared_ptr<Sprite> bodyVertical = nullptr;
};

struct SnakeTailSprites
{
    std::shared_ptr<Sprite> tailUp = nullptr;
    std::shared_ptr<Sprite> tailDown = nullptr;
    std::shared_ptr<Sprite> tailRight = nullptr;
    std::shared_ptr<Sprite> tailLeft = nullptr;
};

class SnakeSegment : public CollisionObject
{
public:    
    SnakeSegment(std::unique_ptr<SpriteRenderer> spriteRenderer, Vector2D position, Vector2D direction);
    SnakeSegment(const SnakeSegment& origin);

    void Update(double elapsedTime) override {}
    void OnCollision(std::shared_ptr<Collision> collision) override {}

    virtual void SetSpriteByDirection();

    Vector2D direction;
    Vector2D prevDirection;

protected:

    static bool spritesLoaded;
    static SnakeHeadSprites headSpriteSet;
    static SnakeSegmentSprites segmentSpriteSet;
    static SnakeTailSprites tailSpriteSet;

private:
    static void LoadSprites();
};

class Snake : public SnakeSegment, public ISubject<std::shared_ptr<SnakeEvent>>
{
public:
    Snake(std::unique_ptr<SpriteRenderer> spriteRenderer, Vector2D position, Vector2D direction);

    void Input(std::shared_ptr<KeyboardEvent> inputEvent) override;
    void OnCollision(std::shared_ptr<Collision> collision) override;
    void SetSpriteByDirection() override;

    void Move();
    void Grow();

    void Attach(std::shared_ptr<IObserver<std::shared_ptr<SnakeEvent>>> observer) override;
    void Detach(std::shared_ptr<IObserver<std::shared_ptr<SnakeEvent>>> observer) override;
    void Notify(std::shared_ptr<SnakeEvent> message) override;

private:
    bool alive;
    bool isMoving;
    
    std::vector<SnakeSegment*> segments;

    std::shared_ptr<IObserver<std::shared_ptr<SnakeEvent>>> observer;
};

class SnakeTail : public SnakeSegment
{
public:
    SnakeTail(std::unique_ptr<SpriteRenderer> spriteRenderer, Vector2D position, Vector2D direction);
    SnakeTail(const SnakeSegment& origin);
protected:
    void SetSpriteByDirection() override;    
};