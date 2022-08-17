#pragma once

#include <memory>

#include "../rendering/sprite.hpp"
#include "../events/input_listener.hpp"

class GameObject : public IInpupListener
{
public:
    virtual void Update(double elapsedTime) {}
    virtual void Input(std::shared_ptr<KeyboardEvent> inputEvent) override {}

    bool IsDrawable();
    bool HandlesInput();
    void SetSprite(std::shared_ptr<Sprite>);
    std::shared_ptr<Sprite> GetSprite();

    //TODO: make specific class for position
    double posX = 0;
    double posY = 0;

protected:
    std::shared_ptr<Sprite> sprite = nullptr;
    bool handlesInput = false; 
};