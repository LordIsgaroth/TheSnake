#pragma once

#include <string>
#include <memory>
#include <vector>

#include <iostream>

#include "my_little_engine/my_little_engine.hpp"

#include "game_controller.hpp"
#include "snake.hpp"

class SnakeGame
{
public:
    SnakeGame();
    void Start();

private:

    const int SCREEN_WIDTH = 880;
    const int SCREEN_HEIGHT = 720;
    const int TILE_SIZE = 40;
    const int FIELD_WIDTH = 20;
    const int FIELD_HEIGHT = 16;
    const int MIN_APPLES = 1;
};