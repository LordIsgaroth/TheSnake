#pragma once

#include <vector>
#include <memory>

#include <SDL2/SDL.h>

#include "event_subject.hpp"
#include "keyboard_event.hpp"
#include "keyboard_listener.hpp"
#include "../game_window.hpp"

class EventHandler
{
public:
    EventHandler();
    ~EventHandler();
    void AddQuitEventListener(std::shared_ptr<GameWindow> listener);
    void AddKeyboardEventListener(std::shared_ptr<KeyboardListener> listener);
    void CheckEvents();
private:
    void QuitNotify(SDL_Event event);
    
    EventSubject<bool> quitEventNotifier;
    EventSubject<std::shared_ptr<KeyboardEvent>> keyboardEventNotifier;
};