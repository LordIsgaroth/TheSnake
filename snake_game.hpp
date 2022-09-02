#pragma once

#include <string>
#include <memory>
#include <vector>

#include <iostream>

#include "my_little_engine/my_little_engine.hpp"

#include "snake.hpp"
#include "apple.hpp"

class SnakeGame
{
public:
    SnakeGame();
    void Start();

private:

    const int SCREEN_WIDTH = 1024;
    const int SCREEN_HEIGHT = 768;

};