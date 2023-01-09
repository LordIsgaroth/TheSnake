#pragma once

#include <vector>
#include <memory>
#include <SDL2/SDL.h>

#include "my_little_engine/core/engine.hpp"

#include "event_subject.hpp"
#include "input_listener.hpp"

class EventHandler
{
public:
    EventHandler();

    void AddInputEventListener(std::shared_ptr<IInputListener> listener);
    void RemoveInputEventListener(std::shared_ptr<IInputListener> listener);

    void CheckEvents();
private:
    //void QuitNotify(SDL_Event event);
    
    EventSubject<std::shared_ptr<SDL_Event>> inputEventNotifier;
};