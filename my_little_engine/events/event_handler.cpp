#include "event_handler.hpp"

EventHandler::EventHandler()
{
    //quitEventNotifier = new EventSubject<bool>();
    quitEventNotifier.SetMessage(true);

    //keyboardEventNotifier = new EventSubject<std::shared_ptr<KeyboardEvent>>();
}

void EventHandler::AddQuitEventListener(std::shared_ptr<GameWindow> listener)
{
    quitEventNotifier.Attach(listener);
}

void EventHandler::AddKeyboardEventListener(std::shared_ptr<IInpupListener> listener)
{
    keyboardEventNotifier.Attach(listener);
}

void EventHandler::CheckEvents()
{
    SDL_Event event;

    while (SDL_PollEvent(&event) != 0)
    {
        if(event.type == SDL_QUIT)
        {
            quitEventNotifier.Notify();
        }
        else if (event.type == SDL_KEYDOWN)
        {
            std::shared_ptr<KeyboardEvent> keyboardEvent = std::make_shared<KeyboardEvent>();
            keyboardEvent->eventType = KeyboardEventType::pressed;
            keyboardEvent->key = event.key.keysym.sym;

            keyboardEventNotifier.SetMessage(keyboardEvent);
            keyboardEventNotifier.Notify();
        }
    }
}

EventHandler::~EventHandler()
{
    //delete quitEventNotifier;
}