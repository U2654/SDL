//
//  main.cpp
//  SDL_Pong
//

// Required SDL include
#include <SDL.h>
#include <iostream>

#include "game.hpp"

//Screen dimension constants
const int WinWidth = 400;
const int WinHeight = 200;


int main( int argc, char* args[] )
{
    Game game;
    
    if (!game.init(WinWidth, WinHeight))
    {
        return -1;
    }
    game.loop();
    game.cleanup();
    
    return 0;
}
