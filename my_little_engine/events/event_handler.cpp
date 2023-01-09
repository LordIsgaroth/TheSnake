#include "event_handler.hpp"

EventHandler::EventHandler() {}

void EventHandler::AddInputEventListener(std::shared_ptr<IInputListener> listener)
{
    inputEventNotifier.Attach(listener);
}

void EventHandler::RemoveInputEventListener(std::shared_ptr<IInputListener> listener)
{
    inputEventNotifier.Detach(listener);
}

void EventHandler::CheckEvents()
{
    SDL_Event event;

    while (SDL_PollEvent(&event) != 0)
    {
        if(event.type == SDL_QUIT) Engine::Quit();
        else if (event.type == SDL_KEYDOWN || event.type == SDL_MOUSEBUTTONUP)
        {
            inputEventNotifier.Notify(std::make_shared<SDL_Event>(event));
        }     
    }
}