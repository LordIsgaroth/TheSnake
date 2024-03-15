#include <stdio.h>

#include "snake_game.hpp"

int main(int argc, char* args[])
{
    
    try
    {
        SnakeGame game;
        game.Load();
        game.Start();

        Engine::Free();
    }
    catch(const char* e)
    {
        printf("%s\n", e);
    }

    return 0;
}