#include "snake_event.hpp"

SnakeEvent::SnakeEvent(SnakeEventType type)
{
    this->type = type;    
}

const SnakeEventType SnakeEvent::Type() const
{
    return type;
}