#pragma once

#include "key.hpp"

enum KeyboardEventType
{
    pressed = 0,
    released
};

struct KeyboardEvent
{
    Key key;
    KeyboardEventType eventType;
};