#include "snake.hpp"

Snake::Snake(std::unique_ptr<SnakeHeadSprites> headSprites)
{
    handlesInput = true;

    this->headSprites = std::move(headSprites);
    SetSprite(this->headSprites->headUp);
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