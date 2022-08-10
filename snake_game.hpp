#pragma once

#include <string>

#include "my_little_engine.hpp"

#include "snake.hpp"

class SnakeGame : IObserver<bool>
{
public:
    SnakeGame();
    void Start();
private:

    const int SCREEN_WIDTH = 1024;
    const int SCREEN_HEIGHT = 768;

    GameWindow *mainWindow = nullptr;
    Renderer* renderer = nullptr;
    EventHandler* eventHandler;
    KeyboardListener* keyboardListener;

    std::shared_ptr<Snake> snake;
    int step = 0; 

    bool quit = false;

    void Update(bool message) override;

    bool Init();
    void MainLoop();
    void Quit();
    void Close();
};