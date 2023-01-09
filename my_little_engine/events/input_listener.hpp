#pragma once

#include <memory>

#include "my_little_engine/common/IObserver.hpp"

class IInputListener : public IObserver<std::shared_ptr<SDL_Event>>
{
private:
    void OnNotify(std::shared_ptr<SDL_Event> message) override
    {
        Input(message);
    }

    virtual void Input(std::shared_ptr<SDL_Event> inputEvent) = 0;
};