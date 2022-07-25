#include "game_window.hpp"

bool GameWindow::SDL_initialized = false;

GameWindow::GameWindow(const char *label, int width, int height)
{
    if(!SDL_initialized)
    {
        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            throw SDL_GetError();
        }

        SDL_initialized = true;
    }
    
    sdl_window = SDL_CreateWindow(label, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
}

GameWindow::~GameWindow()
{
    SDL_DestroyWindow(sdl_window);
}