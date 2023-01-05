#pragma once

#include <SDL2/SDL.h>

enum MouseEventType
{
    down = 0,
    up
};

struct MouseEvent
{
    MouseEventType eventType;
    SDL_MouseButtonEvent eventData;
};
