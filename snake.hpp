#pragma once

#include "my_little_engine/objects/controllable_object.hpp"

class Snake : public ControllableObject
{
public:
    void Update(double elapsedTime) override; 
};