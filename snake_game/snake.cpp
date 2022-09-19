#include "snake.hpp"

//for testing - remove
#include <iostream>

Snake::Snake(std::unique_ptr<SpriteRenderer> spriteRenderer, std::unique_ptr<SnakeHeadSprites> headSprites) : CollisionObject(std::move(spriteRenderer))
{
    name = "Snake";
    handlesInput = true;
    canCollide = true;
    alive = true;

    this->headSprites = std::move(headSprites);
    
    this->spriteRenderer->SetSprite(this->headSprites->headRight);
    
    borders->width = this->spriteRenderer->GetRect()->w;
    borders->height = this->spriteRenderer->GetRect()->h;
}

void Snake::Update(double elapsedTime)
{
    position.x += elapsedTime * speed * direction.x;  
    position.y += elapsedTime * speed * direction.y;
}

void Snake::Input(std::shared_ptr<KeyboardEvent> inputEvent)
{
    if (!alive) return;

    if (inputEvent->eventType == KeyboardEventType::pressed)
    {
        switch (inputEvent->key)
        {
            case SDLK_UP:
            {
                if(direction == Vector2D::Down() || direction == Vector2D::Up()) return;

                nextDirection = Vector2D::Up();
                spriteRenderer->SetSprite(headSprites->headUp);
                break;
            }
            case SDLK_DOWN:
            {
                if(direction == Vector2D::Up() || direction == Vector2D::Down()) return;

                nextDirection = Vector2D::Down();
                spriteRenderer->SetSprite(headSprites->headDown);
                break;
            }
            case SDLK_LEFT:
            {
                if(direction == Vector2D::Right() || direction == Vector2D::Left()) return;

                nextDirection = Vector2D::Left();
                spriteRenderer->SetSprite(headSprites->headLeft);
                break;
            }
            case SDLK_RIGHT:
            {
                if(direction == Vector2D::Left() || direction == Vector2D::Right()) return;

                nextDirection = Vector2D::Right();
                spriteRenderer->SetSprite(headSprites->headRight);
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
        std::shared_ptr<SnakeEvent> event = std::make_shared<SnakeEvent>(SnakeEventType::AppleEaten);
        observer->OnNotify(event);

        Engine::RemoveObject(collision->Other()->Id());
    }
    else if (collision->Other()->Name() == "Border")
    {
        alive = false;
        canCollide = false;
        speed = 0;
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