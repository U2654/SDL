//
//  game.hpp
//  SDL_Pong
//

#ifndef game_hpp
#define game_hpp

#include <SDL.h>
#include <SDL_ttf.h>

#include "graphicsobject.hpp"

class Game
{
public:
    Game();
    
    //! init SDL with window size, init all object, return true if everything fine
    bool init(int f_width, int f_height);

    //! enter the game loop processing
    void loop();
    
    //! clean up
    void cleanup();

private:
    void setupObjects();
    void render();
    void handleCollisions();
    
    int m_width, m_height;

    SDL_Window* m_window;
    SDL_Renderer* m_renderer;

    GraphicsObject* m_topBorder;
    GraphicsObject* m_rightBorder;
    GraphicsObject* m_bottomBorder;

    GraphicsObject* m_leftPaddle;
    GraphicsObject* m_ball;

    float m_ballVx, m_ballVy;
    float m_ballX, m_ballY;
    
    const int PaddleX = 30;
    const int PaddleW = 10;
    const int PaddleH = 40;
    
    const int BorderThickness = 10;

    const int BallSize = 10;
    const float BallVelocity = 4;

    TTF_Font* m_font;
    const char* m_text;
};



#endif /* game_hpp */
