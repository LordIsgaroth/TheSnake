#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string> 

class SnakeGame
{
public:
    SnakeGame();
    void Start();
private:

    const int SCREEN_WIDTH = 1024;
    const int SCREEN_HEIGHT = 768;

    SDL_Window *mainWindow = nullptr;
    //SDL_Surface *screenSurface = nullptr;

    bool Init();
    void MainLoop();
    void Close();

    //SDL_Surface* loadSurface(std::string path);
};