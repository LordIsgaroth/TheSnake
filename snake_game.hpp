#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "game_window.hpp"
#include "renderer.hpp"
#include "sprite.hpp"

class SnakeGame
{
public:
    SnakeGame();
    void Start();
private:

    const int SCREEN_WIDTH = 1024;
    const int SCREEN_HEIGHT = 768;

    GameWindow *mainWindow = nullptr;
    Renderer* renderer = nullptr;

    bool Init();
    void MainLoop();
    void Close();

};