// Required SDL include
#include <SDL.h>
#include <iostream>

//Screen dimension constants
const int WinWidth = 400;
const int WinHeight = 200;

int main( int argc, char* args[] )
{
    // init sdl with video subsystem only and check if succeeded
    if( SDL_Init(SDL_INIT_VIDEO) < 0 )
    {
        std::cout << "Error initializing SDL: " <<  SDL_GetError() << std::endl;
        return -1;
    }
    // create window
    SDL_Window* sdlWindow = SDL_CreateWindow( "SDL Window",
                                             SDL_WINDOWPOS_UNDEFINED,
                                             SDL_WINDOWPOS_UNDEFINED,
                                             WinWidth, WinHeight,
                                             SDL_WINDOW_SHOWN );
    // and check if succeeded
    if(!sdlWindow)
    {
        std::cout << "Error creating window: " <<  SDL_GetError() << std::endl;
        return -2;
    }

    // try some gfx, prefer renderer
    SDL_Renderer* sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, 0);

    // attention... now leaving out checks

    // clear background
    // 1. set color to blue (r, g, b, a)
    SDL_SetRenderDrawColor(sdlRenderer, 0x00, 0x00, 0xa0, 0xff);
    // 2. clear all
    SDL_RenderClear(sdlRenderer);

    // draw a rect
    // 1. set color to cyan (r, g, b, a)
    SDL_SetRenderDrawColor(sdlRenderer, 0x00, 0xa0, 0xa0, 0xff);
    // specify recht
    // clear background: 1. specify rect
    SDL_Rect sdlRect = { 100, 50, 200, 100};
    SDL_RenderFillRect(sdlRenderer, &sdlRect);

    // and show result
    SDL_RenderPresent(sdlRenderer);
    
    // wait until exit
    bool quit = false;
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }
    }

    // clean up
    SDL_DestroyWindow( sdlWindow );
    // finish
    SDL_Quit();
    
    return 0;
}
