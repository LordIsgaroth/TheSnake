#include "snake.hpp"

Snake::Snake(std::unique_ptr<SnakeHeadSprites> headSprites)
{
    this->headSprites = std::move(headSprites);
    SetSprite(this->headSprites->headUp);
}

void Snake::Update(double elapsedTime)
{
    std::shared_ptr<KeyboardEvent> currEvent;

    currEvent = keyboardListener->GetEvent();

    if (currEvent)
    {
        if (currEvent->eventType == KeyboardEventType::pressed)
        {
            switch (currEvent->key)
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

    posX += elapsedTime * speed * dirX;  
    posY += elapsedTime * speed * dirY;    
};