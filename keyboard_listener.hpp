#pragma once

#include <queue>
#include <memory>

#include "IObserver.hpp"
#include "keyboard_event.hpp"

class KeyboardListener : public IObserver<std::shared_ptr<KeyboardEvent>> 
{
public:
    void Update(std::shared_ptr<KeyboardEvent> message) override;
    std::shared_ptr<KeyboardEvent> GetEvent();
    
private:
    std::queue<std::shared_ptr<KeyboardEvent>> eventQueue;
};