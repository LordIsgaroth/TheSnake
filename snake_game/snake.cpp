#include "snake.hpp"

//for testing - remove
#include <iostream>

Snake::Snake(std::unique_ptr<SnakeHeadSprites> headSprites)
{
    handlesInput = true;
    name = "Snake";
    alive = true;

    this->headSprites = std::move(headSprites);
    
    SetSprite(this->headSprites->headRight);
    
    borders->width = sprite->Width();
    borders->height = sprite->Height();
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
                direction = Vector2D::Up();
                SetSprite(headSprites->headUp);
                break;
            }
            case SDLK_DOWN:
            {
                direction = Vector2D::Down();
                SetSprite(headSprites->headDown);
                break;
            }
            case SDLK_LEFT:
            {
                direction = Vector2D::Left();
                SetSprite(headSprites->headLeft);
                break;
            }
            case SDLK_RIGHT:
            {
                direction = Vector2D::Right();
                SetSprite(headSprites->headRight);
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