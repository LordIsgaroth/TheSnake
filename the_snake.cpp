
#include <stdio.h>
#include "snake_game.hpp"

int main()
{
    try
    {
        SnakeGame game;
        game.Start();
    }
    catch(const char* e)
    {
        printf("%s\n", e);
    }

    return 0;
}