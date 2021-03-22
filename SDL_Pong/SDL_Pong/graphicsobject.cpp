//
//  graphicsobject.cpp
//  SDL_Pong
//

#include "graphicsobject.hpp"

GraphicsObject::GraphicsObject(int f_x, int f_y, int f_width, int f_height)
: m_r(0), m_g(0), m_b(0)
{
    m_rect = {f_x, f_y, f_width, f_height};
}

void GraphicsObject::setPosition(int f_x, int f_y)
{
    m_rect.x = f_x;
    m_rect.y = f_y;
}

void GraphicsObject::setColor(unsigned char f_r, unsigned char f_g, unsigned char f_b)
{
    m_r = f_r;
    m_g = f_g;
    m_b = f_b;
}

void GraphicsObject::render(SDL_Renderer* f_renderer)
{
    // set color
    SDL_SetRenderDrawColor(f_renderer, m_r, m_g, m_b, 0xff);
    // specify rect
    SDL_RenderFillRect(f_renderer, &m_rect);
}


