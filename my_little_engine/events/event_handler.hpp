#pragma once

#include <vector>
#include <memory>
#include <SDL.h>

#include "core/engine.hpp"

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