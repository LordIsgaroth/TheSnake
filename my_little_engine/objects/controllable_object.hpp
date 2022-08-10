#pragma once

#include "game_object.hpp"
#include "../events/keyboard_listener.hpp"

class ControllableObject : public GameObject
{
private:
    KeyboardListener keyboardListener;
};