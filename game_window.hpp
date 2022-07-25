#pragma once

#include <SDL2/SDL.h>
//#include <SDL2/SDL_image.h>
//#include <string>

class GameWindow
{
public:

    GameWindow(const char *label, int width, int height);
    ~GameWindow();
    SDL_Window* window() { return sdl_window; } 

private:
    static bool SDL_initialized;
    SDL_Window *sdl_window = nullptr;
    
    
};