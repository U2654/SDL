//
//  game.cpp
//  SDL_Pong
//

#include "game.hpp"
#include "collision.hpp"

#include <iostream>

Game::Game()
{
}

bool Game::init(int f_width, int f_height)
{
    // init sdl with video subsystem only and check if succeeded
    if( SDL_Init(SDL_INIT_VIDEO) < 0 )
    {
        std::cout << "Error initializing SDL: " <<  SDL_GetError() << std::endl;
        return false;
    }
    
    m_width = f_width;
    m_height = f_height;
    
    // create window
    m_window = SDL_CreateWindow( "SDL Window",
                                 SDL_WINDOWPOS_UNDEFINED,
                                 SDL_WINDOWPOS_UNDEFINED,
                                 m_width, m_height,
                                 SDL_WINDOW_SHOWN );
    // and check if succeeded
    if(!m_window)
    {
        std::cout << "Error creating window: " <<  SDL_GetError() << std::endl;
        return false;
    }
    
    if (TTF_Init() < 0)
    {
        std::cout << "Error initializing SDL_ttf: " <<  TTF_GetError() << std::endl;
        return false;
    }

    m_font = TTF_OpenFont("/Library/Fonts/Microsoft/Arial.ttf", 24);
    if (!m_font)
    {
        std::cout << "Error openen ttf font: " <<  TTF_GetError() << std::endl;
        return false;
    }
    
    // try some gfx, prefer renderer
    m_renderer = SDL_CreateRenderer(m_window, -1, 0);

    // setup objects
    setupObjects();

    //
    m_text = "Go";
    return true;
}

void Game::cleanup()
{
    // clean up
    SDL_DestroyWindow(m_window);
    SDL_DestroyRenderer(m_renderer);
    
    TTF_CloseFont(m_font);

    // finish
    SDL_Quit();
    TTF_Quit();

    // delete all objects
    delete m_topBorder;
    delete m_rightBorder;
    delete m_bottomBorder;
    delete m_leftPaddle;
    delete m_ball;
}

void Game::setupObjects()
{
    m_rightBorder = new GraphicsObject(m_width-BorderThickness, 0, BorderThickness, m_height);
    m_rightBorder->setColor(0x00, 0x00, 0xa0);

    m_topBorder = new GraphicsObject(0, 0, m_width, BorderThickness);
    m_topBorder->setColor(0x00, 0x00, 0xa0);
    
    m_bottomBorder = new GraphicsObject(0, m_height-BorderThickness, m_width, BorderThickness);
    m_bottomBorder->setColor(0x00, 0x00, 0xa0);

    m_leftPaddle = new GraphicsObject(PaddleX, BorderThickness, PaddleW, PaddleH);
    m_leftPaddle->setColor(0x00, 0xa0, 0xa0);

    m_ballVx = -BallVelocity/sqrt(2);
    m_ballVy = m_ballVx;
    m_ballX = m_width - BallSize - BorderThickness;
    m_ballY = m_height / 2;
    m_ball = new GraphicsObject(int(m_ballX), int(m_ballY), BallSize, BallSize);
    m_ball->setColor(0x80, 0x80, 0x80);
}


void Game::handleCollisions() {
    if (checkCollision(m_topBorder, m_ball) && (m_ballVy < 0.0f))
    {
        m_ball->setPosition(m_ball->x(), m_topBorder->bottom());
        m_ballVy *= -1;
    }
    if (checkCollision(m_rightBorder, m_ball) && (m_ballVx > 0.0f))
    {
        m_ball->setPosition(m_rightBorder->left()-m_ball->width(), m_ball->y());
        m_ballVx *= -1;
    }
    if (checkCollision(m_bottomBorder, m_ball) && (m_ballVy > 0.0f) )
    {
        m_ball->setPosition(m_ball->x(), m_bottomBorder->top()-m_ball->height());
        m_ballVy *= -1;
    }
    
    CollisionType cs = checkCollision(m_leftPaddle, m_ball);
    if ((cs & RIGHT) && (m_ballVx < 0.0f))
    {
        m_ball->setPosition(m_leftPaddle->right(), m_ball->y());

        // some jitter behaviour
        float tv = float(m_leftPaddle->cy() - m_ball->cy()) / float(PaddleH-BallSize);
        m_ballVy = 2.0f*tv*m_ballVx;

        // norm and set to wanted velocity
        float vabs = sqrt(m_ballVx*m_ballVx + m_ballVy*m_ballVy);
        m_ballVx /= vabs;
        m_ballVy /= vabs;
        m_ballVx *= -BallVelocity;
        m_ballVy *= BallVelocity;

        // vanish text by first hit
        m_text = " ";
    }
    else if ((cs & TOP) && (m_ballVx < 0.0f))
    {
        m_ball->setPosition(m_ball->x(), m_leftPaddle->top()-m_ball->height());
        m_ballVx *= -1;
        m_ballVy *= -1;
    }
    else if ((cs & BOTTOM) && (m_ballVx < 0.0f))
    {
        m_ball->setPosition(m_ball->x(), m_leftPaddle->bottom());
        m_ballVx *= -1;
        m_ballVy *= -1;
    }
}

void Game::render()
{
    // clear background
    // 1. set color to blue (r, g, b, a)
    SDL_SetRenderDrawColor(m_renderer, 0x00, 0x00, 0x50, 0xff);
    // 2. clear all
    SDL_RenderClear(m_renderer);
    
    // render borders
    m_topBorder->render(m_renderer);
    m_rightBorder->render(m_renderer);
    m_bottomBorder->render(m_renderer);
    
    // paddle and
    m_leftPaddle->render(m_renderer);
    // ball
    m_ball->render(m_renderer);
    
    // text
    SDL_Color white = {0xff, 0xff, 0xff};
    SDL_Surface* textSurf = TTF_RenderText_Solid(m_font, m_text, white);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, textSurf);
    SDL_Rect rect = {0, 0, textSurf->w, textSurf->h};
    SDL_RenderCopy(m_renderer, texture, NULL, &rect);
    SDL_FreeSurface(textSurf);
    SDL_DestroyTexture(texture);

    // and show result
    SDL_RenderPresent(m_renderer);
}

void Game::loop()
{
    // wait until exit
    bool quit = false;
    SDL_Event e;
    while (!quit)
    {
        // framerate consideration
        unsigned int startTime = SDL_GetTicks();

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }
        
        // handle input
        int x, y;
        SDL_GetMouseState(&x, &y);

        // check y
        y = (y < BorderThickness)? BorderThickness : y;
        y = (y> m_height - PaddleH - BorderThickness) ? m_height - (PaddleH+BorderThickness): y;

        // set left paddle according to mouse movement
        m_leftPaddle->setPosition(PaddleX, y);

        // move ball with velocity
        m_ballX += m_ballVx;
        m_ballY += m_ballVy;
        m_ball->setPosition(int(m_ballX), int(m_ballY));

        // render all
        render();

        // now handle collisions for next loop run
        handleCollisions();

        // ball lost?
        if (m_ball->x() < 0)
        {
            m_ballX = m_width - BallSize - BorderThickness;
            m_ball->setPosition(int(m_ballX), int(m_ballY));
            m_text = "Next Try";
        }
        
        // to achieve desired frame rate
        unsigned int endTime = SDL_GetTicks();
        unsigned int deltaTime = endTime-startTime;
        // 16 approx 1000/60 for 60 Hz, this time magic number for the two lines
        if (deltaTime < 16)
        {
            SDL_Delay(16-deltaTime);
        }
    }
}
