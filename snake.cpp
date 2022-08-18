#include "snake.hpp"

//for testing - remove
#include <iostream>

Snake::Snake(std::unique_ptr<SnakeHeadSprites> headSprites)
{
    name = "Snake";
    handlesInput = true;

    this->headSprites = std::move(headSprites);
    SetSprite(this->headSprites->headUp);

    borders->width = sprite->Width();
    borders->width = sprite->Height();
}

void Snake::Update(double elapsedTime)
{
    posX += elapsedTime * speed * dirX;  
    posY += elapsedTime * speed * dirY;    
}

void Snake::Input(std::shared_ptr<KeyboardEvent> inputEvent)
{
    if (inputEvent->eventType == KeyboardEventType::pressed)
    {
        switch (inputEvent->key)
        {
            case SDLK_UP:
            {
                dirX = 0;
                dirY = -1;
                SetSprite(headSprites->headUp);
                break;
            }
            case SDLK_DOWN:
            {
                dirX = 0;
                dirY = 1;
                SetSprite(headSprites->headDown);
                break;
            }
            case SDLK_LEFT:
            {
                dirX = -1;
                dirY = 0;
                SetSprite(headSprites->headLeft);
                break;
            }
            case SDLK_RIGHT:
            {
                dirX = 1;
                dirY = 0;
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
}