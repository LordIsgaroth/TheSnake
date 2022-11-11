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
    spriteRenderer = std::make_unique<SpriteRenderer>(*origin.GetSpriteRenderer());

    direction = origin.direction;

    borders->width = spriteRenderer->GetRect().w;
    borders->height = spriteRenderer->GetRect().h;
}

void SnakeSegment::LoadSprites()
{
    headSpriteSet.headUp = Engine::GetRenderer().CreateSprite("Graphics/head_up.png");
    headSpriteSet.headDown = Engine::GetRenderer().CreateSprite("Graphics/head_down.png");
    headSpriteSet.headLeft = Engine::GetRenderer().CreateSprite("Graphics/head_left.png");
    headSpriteSet.headRight = Engine::GetRenderer().CreateSprite("Graphics/head_right.png");    

    segmentSpriteSet.bodyBottomLeft = Engine::GetRenderer().CreateSprite("Graphics/body_bottomleft.png");
    segmentSpriteSet.bodyBottomRight = Engine::GetRenderer().CreateSprite("Graphics/body_bottomright.png");
    segmentSpriteSet.bodyTopLeft = Engine::GetRenderer().CreateSprite("Graphics/body_topleft.png");
    segmentSpriteSet.bodyTopRight = Engine::GetRenderer().CreateSprite("Graphics/body_topright.png");
    segmentSpriteSet.bodyHorizontal = Engine::GetRenderer().CreateSprite("Graphics/body_horizontal.png");
    segmentSpriteSet.bodyVertical = Engine::GetRenderer().CreateSprite("Graphics/body_vertical.png");

    tailSpriteSet.tailUp = Engine::GetRenderer().CreateSprite("Graphics/tail_up.png");
    tailSpriteSet.tailDown = Engine::GetRenderer().CreateSprite("Graphics/tail_down.png");
    tailSpriteSet.tailLeft = Engine::GetRenderer().CreateSprite("Graphics/tail_left.png");
    tailSpriteSet.tailRight = Engine::GetRenderer().CreateSprite("Graphics/tail_right.png");
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

    SetSpriteByDirection();

    borders->width = this->spriteRenderer->GetRect().w;
    borders->height = this->spriteRenderer->GetRect().h;

    segments.push_back(this);

    std::shared_ptr<SnakeSegment> snakeSegment = std::make_shared<SnakeSegment>(*this);
    snakeSegment->position = Vector2D(position.X() - borders->width, position.Y());    
    segments.push_back(snakeSegment.get());
    Engine::AddObject(snakeSegment);

    std::shared_ptr<SnakeTail> snakeTail = std::make_shared<SnakeTail>(*this);
    snakeTail->position = Vector2D(position.X() - 2 * borders->width, position.Y());
    segments.push_back(snakeTail.get());
    Engine::AddObject(snakeTail);
}

void Snake::Move()
{
    if (isMoving)
    {
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
        if(!segment->GetSpriteRenderer()->visible) segment->GetSpriteRenderer()->visible = true;
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
    newSegment->GetSpriteRenderer()->visible = false;

    Vector2D newSegmentPos = segments[segments.size() - 1]->position;
    newSegment->position = newSegmentPos;
    newSegment->SetSpriteByDirection();

    Engine::AddObject(newSegment);

    segments.insert(--segments.end(), newSegment.get());
}

void Snake::Input(std::shared_ptr<KeyboardEvent> inputEvent)
{
    if (!alive) return;

    if (inputEvent->eventType == KeyboardEventType::pressed)
    {
        if (!isMoving) isMoving = true;

        switch (inputEvent->key)
        {
            case SDLK_UP:
            {
                if (direction == Vector2D::Down() || direction == Vector2D::Up()) return;

                direction = Vector2D::Up();
                break;
            }
            case SDLK_DOWN:
            {
                if (direction == Vector2D::Up() || direction == Vector2D::Down()) return;

                direction = Vector2D::Down();
                break;
            }
            case SDLK_LEFT:
            {
                if (direction == Vector2D::Right() || direction == Vector2D::Left()) return;

                direction = Vector2D::Left();
                break;
            }
            case SDLK_RIGHT:
            {
                if (direction == Vector2D::Left() || direction == Vector2D::Right()) return;

                direction = Vector2D::Right();
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
        std::shared_ptr<SnakeEvent> event = std::make_shared<SnakeEvent>(SnakeEventType::AppleEaten);
        observer->OnNotify(event);

        Engine::RemoveObject(collision->Other()->Id());
    }
    else if (collision->Other()->Name() == "Border" 
            || collision->Other()->Name() == "Segment"
            || collision->Other()->Name() == "Tail")
    {
        alive = false;
        canCollide = false;
        isMoving = false;
    } 
}

void Snake::Attach(std::shared_ptr<IObserver<std::shared_ptr<SnakeEvent>>> observer)
{
    this->observer = observer;
}

void Snake::Detach(std::shared_ptr<IObserver<std::shared_ptr<SnakeEvent>>> observer)
{
    this->observer = nullptr;
}

void Snake::Notify(std::shared_ptr<SnakeEvent> message)
{
    if(observer) observer->OnNotify(message);
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