#pragma once

#include <memory>

#include "../common/IObserver.hpp"
#include "../events/keyboard_event.hpp"

class IInpupListener : public IObserver<std::shared_ptr<KeyboardEvent>>
{
private:
    void Update(std::shared_ptr<KeyboardEvent> message) override
    {
        Input(message);
    }

    virtual void Input(std::shared_ptr<KeyboardEvent> inputEvent) = 0;
};