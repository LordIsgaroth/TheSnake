#include "snake.hpp"

//for testing - remove
#include <iostream>

bool SnakeSegment::spritesLoaded;
SnakeHeadSprites SnakeSegment::headSpriteSet;
SnakeSegmentSprites SnakeSegment::segmentSpriteSet;
SnakeTailSprites SnakeSegment::tailSpriteSet;

SnakeSegment::SnakeSegment(std::unique_ptr<SpriteRenderer> spriteRenderer, Vector2D position, Vector2D direction) : CollisionObject(std::move(spriteRenderer))
{
    if (!spritesLoaded) LoadSprites();

    name = "Segment";
    canCollide = false;
    
    this->position = position;
    this->direction = direction;
    this->prevDirection = direction;

    SetSpriteByDirection();

    borders->width = this->spriteRenderer->GetRect().w;
    borders->height = this->spriteRenderer->GetRect().h;
}

SnakeSegment::SnakeSegment(const SnakeSegment& origin)
{
    name = "Segment";
    canCollide = true;

    direction = origin.direction;
    prevDirection = origin.prevDirection;
    spriteRenderer = std::make_unique<SpriteRenderer>(origin.GetSpriteRenderer());

    direction = origin.direction;

    borders->width = spriteRenderer->GetRect().w;
    borders->height = spriteRenderer->GetRect().h;
}

void SnakeSegment::LoadSprites()
{
    headSpriteSet.headUp = std::make_shared<Sprite>("Graphics/head_up.png");
    headSpriteSet.headDown = std::make_shared<Sprite>("Graphics/head_down.png");
    headSpriteSet.headLeft = std::make_shared<Sprite>("Graphics/head_left.png");
    headSpriteSet.headRight = std::make_shared<Sprite>("Graphics/head_right.png");    

    segmentSpriteSet.bodyBottomLeft = std::make_shared<Sprite>("Graphics/body_bottomleft.png");
    segmentSpriteSet.bodyBottomRight = std::make_shared<Sprite>("Graphics/body_bottomright.png");
    segmentSpriteSet.bodyTopLeft = std::make_shared<Sprite>("Graphics/body_topleft.png");
    segmentSpriteSet.bodyTopRight = std::make_shared<Sprite>("Graphics/body_topright.png");
    segmentSpriteSet.bodyHorizontal = std::make_shared<Sprite>("Graphics/body_horizontal.png");
    segmentSpriteSet.bodyVertical = std::make_shared<Sprite>("Graphics/body_vertical.png");

    tailSpriteSet.tailUp = std::make_shared<Sprite>("Graphics/tail_up.png");
    tailSpriteSet.tailDown = std::make_shared<Sprite>("Graphics/tail_down.png");
    tailSpriteSet.tailLeft = std::make_shared<Sprite>("Graphics/tail_left.png");
    tailSpriteSet.tailRight = std::make_shared<Sprite>("Graphics/tail_right.png");
}

void SnakeSegment::SetSpriteByDirection()
{
    if (direction == Vector2D::Up())
    {
        if (prevDirection == Vector2D::Right()) spriteRenderer->SetSprite(segmentSpriteSet.bodyTopRight);
        else if (prevDirection == Vector2D::Left()) spriteRenderer->SetSprite(segmentSpriteSet.bodyTopLeft);
        else spriteRenderer->SetSprite(segmentSpriteSet.bodyVertical);
    }
    else if (direction == Vector2D::Down())
    {
        if (prevDirection == Vector2D::Right()) spriteRenderer->SetSprite(segmentSpriteSet.bodyBottomRight);
        else if (prevDirection == Vector2D::Left()) spriteRenderer->SetSprite(segmentSpriteSet.bodyBottomLeft);
        else spriteRenderer->SetSprite(segmentSpriteSet.bodyVertical);
    }
    else if (direction == Vector2D::Right())
    {
        if (prevDirection == Vector2D::Up()) spriteRenderer->SetSprite(segmentSpriteSet.bodyBottomLeft);
        else if (prevDirection == Vector2D::Down()) spriteRenderer->SetSprite(segmentSpriteSet.bodyTopLeft);
        else spriteRenderer->SetSprite(segmentSpriteSet.bodyHorizontal);
    }
    else if (direction == Vector2D::Left())
    {
        if (prevDirection == Vector2D::Up()) spriteRenderer->SetSprite(segmentSpriteSet.bodyBottomRight);
        else if (prevDirection == Vector2D::Down()) spriteRenderer->SetSprite(segmentSpriteSet.bodyTopRight);
        else spriteRenderer->SetSprite(segmentSpriteSet.bodyHorizontal);
    }
    
    else spriteRenderer->SetSprite(nullptr);
}

Snake::Snake(std::unique_ptr<SpriteRenderer> spriteRenderer, Vector2D position, Vector2D direction) 
    : SnakeSegment(std::move(spriteRenderer), position, direction)
{
    name = "Snake";
    handlesInput = true;
    canCollide = true;
    alive = true;
    isMoving = false;

    nextDirection = direction;
    SetSpriteByDirection();

    borders->width = this->spriteRenderer->GetRect().w;
    borders->height = this->spriteRenderer->GetRect().h;

    segments.push_back(this);

    std::shared_ptr<SnakeSegment> snakeSegment = std::make_shared<SnakeSegment>(*this);
    snakeSegment->position = Vector2D(position.X() - borders->width, position.Y());
    snakeSegment->SetSpriteByDirection();    
    segments.push_back(snakeSegment.get());
    Engine::AddObject(snakeSegment);

    std::shared_ptr<SnakeTail> snakeTail = std::make_shared<SnakeTail>(*this);
    snakeTail->position = Vector2D(position.X() - 2 * borders->width, position.Y());
    snakeTail->SetSpriteByDirection();
    segments.push_back(snakeTail.get());
    Engine::AddObject(snakeTail);
}

void Snake::Destroy()
{
    for (SnakeSegment* segment : segments)
    {
        Engine::RemoveObject(segment->Id());
    }

    segments.clear();
}

void Snake::Move()
{
    if (isMoving)
    {
        direction = nextDirection;

        for (int i = segments.size() - 1; i > 0; i--)
        {
            segments[i]->position = segments[i - 1]->position;
            segments[i]->prevDirection = segments[i]->direction;
            segments[i]->direction = segments[i - 1]->direction;
        }

        segments[segments.size() - 1]->direction = segments[segments.size() - 2]->prevDirection;
        position = Vector2D(position.X() + borders->width * direction.X(), position.Y() + borders->height * direction.Y());
    }

    for (SnakeSegment* segment : segments)
    {
        segment->SetSpriteByDirection();
        if(!segment->GetTextureRenderer().visible) segment->GetTextureRenderer().visible = true;
    }
}

void Snake::SetSpriteByDirection()
{
    if (direction == Vector2D::Up()) spriteRenderer->SetSprite(headSpriteSet.headUp);
    else if (direction == Vector2D::Down()) spriteRenderer->SetSprite(headSpriteSet.headDown);
    else if (direction == Vector2D::Right()) spriteRenderer->SetSprite(headSpriteSet.headRight);
    else if (direction == Vector2D::Left()) spriteRenderer->SetSprite(headSpriteSet.headLeft);
    else spriteRenderer->SetSprite(nullptr);
}

void Snake::Grow()
{
    std::shared_ptr<SnakeSegment> newSegment = std::make_shared<SnakeSegment>(*segments[segments.size() - 1]);
    newSegment->GetSpriteRenderer().visible = false;

    Vector2D newSegmentPos = segments[segments.size() - 1]->position;
    newSegment->position = newSegmentPos;
    newSegment->SetSpriteByDirection();

    Engine::AddObject(newSegment);

    segments.insert(--segments.end(), newSegment.get());
}

void Snake::Input(std::shared_ptr<SDL_Event> inputEvent)
{
    if (!alive) return;

    if (inputEvent->type == SDL_KEYDOWN)
    {
        switch (inputEvent->key.keysym.sym)
        {
            case SDLK_UP:
            {
                if (!isMoving) isMoving = true;
                if (direction == Vector2D::Down() || direction == Vector2D::Up()) return;

                nextDirection = Vector2D::Up();
                break;
            }
            case SDLK_DOWN:
            {
                if (!isMoving) isMoving = true;
                if (direction == Vector2D::Up() || direction == Vector2D::Down()) return;

                nextDirection = Vector2D::Down();
                break;
            }
            case SDLK_LEFT:
            {
                if (!isMoving) isMoving = true;
                if (direction == Vector2D::Right() || direction == Vector2D::Left()) return;

                nextDirection = Vector2D::Left();
                break;
            }
            case SDLK_RIGHT:
            {
                if (!isMoving) isMoving = true;
                if (direction == Vector2D::Left() || direction == Vector2D::Right()) return;

                nextDirection = Vector2D::Right();
                break;
            }

            default:
                break;
        }
    }
}

void Snake::OnCollision(std::shared_ptr<Collision> collision)
{
    std::cout << name << " collides with " << collision->Other()->Name() << std::endl;

    if (collision->Other()->Name() == "Apple") 
    {
        Grow();
        OnAppleEaten();

        Engine::RemoveObject(collision->Other()->Id());
    }
    else if (collision->Other()->Name() == "Border" 
            || collision->Other()->Name() == "Segment"
            || collision->Other()->Name() == "Tail")
    {
        alive = false;
        canCollide = false;
        isMoving = false;

        OnSnakeDead();
    } 
}

SnakeTail::SnakeTail(std::unique_ptr<SpriteRenderer> spriteRenderer, Vector2D position, Vector2D direction) 
    : SnakeSegment(std::move(spriteRenderer), position, direction)
{
    name = "Tail";

    canCollide = true;
    SetSpriteByDirection();
}

SnakeTail::SnakeTail(const SnakeSegment& origin) : SnakeSegment(origin)
{
    name = "Tail";
}

void SnakeTail::SetSpriteByDirection()
{
    if (direction == Vector2D::Up()) spriteRenderer->SetSprite(tailSpriteSet.tailUp);
    else if (direction == Vector2D::Down()) spriteRenderer->SetSprite(tailSpriteSet.tailDown);
    else if (direction == Vector2D::Right()) spriteRenderer->SetSprite(tailSpriteSet.tailRight);
    else if (direction == Vector2D::Left()) spriteRenderer->SetSprite(tailSpriteSet.tailLeft);
    else spriteRenderer->SetSprite(nullptr);        
}