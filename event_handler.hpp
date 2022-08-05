#pragma once

#include <vector>
#include <memory>

#include <SDL2/SDL.h>

#include "event_subject.hpp"
#include "keyboard_event.hpp"
#include "keyboard_listener.hpp"
#include "IObserver.hpp"

class EventHandler
{
public:
    EventHandler();
    ~EventHandler();
    void AddQuitEventListener(IObserver<bool> *listener);
    void AddKeyboardEventListener(KeyboardListener *listener);
    void CheckEvents();
private:
    void QuitNotify(SDL_Event event);
    
    EventSubject<bool> *quitEventNotifier;
    EventSubject<std::shared_ptr<KeyboardEvent>> *keyboardEventNotifier;
};