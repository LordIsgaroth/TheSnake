#include "event_handler.hpp"

EventHandler::EventHandler() {}

void EventHandler::AddInputEventListener(std::shared_ptr<IInputListener> listener)
{
    keyboardEventNotifier.Attach(listener);
}

void EventHandler::RemoveInputEventListener(std::shared_ptr<IInputListener> listener)
{
    keyboardEventNotifier.Detach(listener);
}

void EventHandler::CheckEvents()
{
    SDL_Event event;

    while (SDL_PollEvent(&event) != 0)
    {
        if(event.type == SDL_QUIT) Engine::Quit();
        else if (event.type == SDL_KEYDOWN)
        {
            std::shared_ptr<KeyboardEvent> keyboardEvent = std::make_shared<KeyboardEvent>();
            keyboardEvent->eventType = KeyboardEventType::pressed;
            keyboardEvent->key = event.key.keysym.sym;

            keyboardEventNotifier.Notify(keyboardEvent);
        }
        else if (event.type == SDL_MOUSEBUTTONUP)
        {
            std::shared_ptr<MouseEvent> mouseEvent = std::make_shared<MouseEvent>();
            mouseEvent->eventType = MouseEventType::up;
            mouseEvent->eventData = event.button;            
        }       
    }
}