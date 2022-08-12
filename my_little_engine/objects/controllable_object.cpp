#include "controllable_object.hpp"

ControllableObject::ControllableObject()
{
    keyboardListener = std::make_shared<KeyboardListener>();
}

std::shared_ptr<KeyboardListener> ControllableObject::GetKeyboardListener()
{ 
    return keyboardListener;
}