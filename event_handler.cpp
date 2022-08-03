#include "event_handler.hpp"

EventHandler::EventHandler()
{
    quitEventNotifier = new EventSubject<bool>();
    quitEventNotifier->SetMessage(true);
}

void EventHandler::AddQuitEventListener(IObserver<bool> *listener)
{
    quitEventNotifier->Attach(listener);
}

void EventHandler::CheckEvents()
{
    SDL_Event event;

    while (SDL_PollEvent(&event) != 0)
    {
        if(event.type == SDL_QUIT)
        {
            quitEventNotifier->Notify();
        }
    }
}

EventHandler::~EventHandler()
{
    free(quitEventNotifier);
}