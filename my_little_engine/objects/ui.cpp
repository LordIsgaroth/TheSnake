
#include "ui.hpp"

Button::Button(std::string buttonName, std::unique_ptr<SpriteRenderer> spriteRenderer)
{
    handlesInput = true;
    name = buttonName;

    this->spriteRenderer = std::move(spriteRenderer);
}

void Button::Input(std::shared_ptr<KeyboardEvent> inputEvent)
{
    std::cout << inputEvent << std::endl;
}