#pragma once

#include <SDL2/SDL.h>
#include "../common/IObserver.hpp"

class GameWindow : public IObserver<bool>
{
public:
    GameWindow(const char *label, int width, int height);
    ~GameWindow();
    SDL_Window* window() { return sdl_window; }
    void Update(bool message) override;
    bool IsActive();

private:
    bool active = true;
    static bool SDL_initialized;
    SDL_Window *sdl_window = nullptr; 
};