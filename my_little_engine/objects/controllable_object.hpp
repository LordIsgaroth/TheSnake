#pragma once

#include <memory>
#include "game_object.hpp"
#include "../events/keyboard_listener.hpp"

class ControllableObject : public GameObject
{
public:
    ControllableObject();
    std::shared_ptr<KeyboardListener> GetKeyboardListener();    
protected:
    std::shared_ptr<KeyboardListener> keyboardListener;
};