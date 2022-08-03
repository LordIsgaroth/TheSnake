#pragma once

//#include <SDL2/SDL.h>
#include <string>

#include "game_window.hpp"
#include "renderer.hpp"
#include "event_handler.hpp"
#include "sprite.hpp"
#include "IObserver.hpp"

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

    bool quit = false;

    void Update(bool message) override;

    bool Init();
    void MainLoop();
    void EventListener();
    void Quit();
    void Close();
};