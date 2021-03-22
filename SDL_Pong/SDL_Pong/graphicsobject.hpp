//
//  graphicsobject.hpp
//  SDL_Pong
//

#ifndef graphicsobject_hpp
#define graphicsobject_hpp

#include <stdio.h>

#include "SDL.h"

class GraphicsObject
{
public:
    //! construct with position and size
    GraphicsObject(int f_x, int f_y, int f_width, int f_heigt);
    
    //! set color
    void setColor(unsigned char f_r, unsigned char f_g, unsigned char f_b);
    //! set position
    void setPosition(int f_x, int f_y);

    // lot of convience functions
    int x() const { return m_rect.x ;}
    int y() const { return m_rect.y; }
    int left() const { return m_rect.x ;}
    int right() const { return m_rect.x + m_rect.w - 1; }
    int top() const { return m_rect.y ;}
    int bottom() const { return m_rect.y + m_rect.h - 1; }
    int width() const { return m_rect.w; }
    int height() const { return m_rect.h; }
    int cx() const { return m_rect.x + (m_rect.w/2); }
    int cy() const { return m_rect.y + (m_rect.h/2); }
    
    void render(SDL_Renderer* f_renderer);

private:
    //! Rectangles structures
    SDL_Rect m_rect;
    //! color in rgb
    unsigned char m_r, m_g, m_b;
};

#endif /* graphicsobject_hpp */
