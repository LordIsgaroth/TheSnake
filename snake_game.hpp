#pragma once

#include <string>
#include <memory>
#include <chrono>
#include <iostream>

#include "my_little_engine.hpp"

#include "snake.hpp"

class SnakeGame
{
public:
    SnakeGame();
    void Start();
private:

    const int SCREEN_WIDTH = 1024;
    const int SCREEN_HEIGHT = 768;

    std::shared_ptr<GameWindow> mainWindow;
    Renderer* renderer = nullptr;
    EventHandler* eventHandler;

    std::shared_ptr<Snake> snake; 

    bool quit = false;

    void MainLoop();
    void Quit();
    void Close();
};