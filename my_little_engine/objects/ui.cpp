
#include "ui.hpp"

Button::Button(std::string buttonName, std::unique_ptr<SpriteRenderer> spriteRenderer)
{
    handlesInput = true;
    name = buttonName;

    this->spriteRenderer = std::move(spriteRenderer);
}

void Button::Input(std::shared_ptr<SDL_Event> inputEvent)
{
    if(inputEvent->type == SDL_MOUSEBUTTONUP)
    {
        Vector2D mousePosition(inputEvent->button.x, inputEvent->button.y);

        position.X();
        position.Y();

        if(PointInRect(mousePosition, position, GetSpriteRenderer().GetRect()))
        {
            std::cout << "Button pressed!" << std::endl;
        }
    }
}

bool Button::PointInRect(Vector2D point, Vector2D rectPosition, const SDL_Rect& rect)
{
    bool inRangeByX = point.X() >= rectPosition.X() && point.X() <= rectPosition.X() + rect.w;
    bool inRangeByY = point.Y() >= rectPosition.Y() && point.Y() <= rectPosition.Y() + rect.h; 

    if (inRangeByX && inRangeByY) return true;
    else return false;
}