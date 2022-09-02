#pragma once

#include <memory>

#include "my_little_engine/common/IObserver.hpp"
#include "my_little_engine/events/keyboard_event.hpp"

class IInputListener : public IObserver<std::shared_ptr<KeyboardEvent>>
{
private:
    void Update(std::shared_ptr<KeyboardEvent> message) override
    {
        Input(message);
    }

    virtual void Input(std::shared_ptr<KeyboardEvent> inputEvent) = 0;
};