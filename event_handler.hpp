#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include "event_subject.hpp"
#include "IObserver.hpp"

class EventHandler
{
public:
    EventHandler();
    ~EventHandler();
    void AddQuitEventListener(IObserver<bool> *listener);
    void CheckEvents();
private:
    void QuitNotify(SDL_Event event);
    
    EventSubject<bool> *quitEventNotifier = nullptr;
};