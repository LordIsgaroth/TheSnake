#include "keyboard_listener.hpp"

void KeyboardListener::Update(std::shared_ptr<KeyboardEvent> message)
{
    eventQueue.push(message);
}

std::shared_ptr<KeyboardEvent> KeyboardListener::GetEvent()
{
    std::shared_ptr<KeyboardEvent> result = nullptr;

    if(!eventQueue.empty()) 
    {
        result = eventQueue.front(); 
        eventQueue.pop();    
    }
    
    return result;
}