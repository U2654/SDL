//
//  collision.cpp
//  SDL_Pong
//

#include "collision.hpp"
#include <stdlib.h>

CollisionType checkCollision(const GraphicsObject* f_obj1, const GraphicsObject* f_obj2)
{
    CollisionType cs = NONE;
    
    int ox1 = f_obj1->left() - f_obj2->right();
    int oy1 = f_obj1->top() - f_obj2->bottom();

    int ox2 = f_obj2->left() - f_obj1->right();
    int oy2 = f_obj2->top() - f_obj1->bottom();

    // far away
    if ((ox1 > 0) || (oy1 > 0) || (ox2 > 0)|| (oy2 > 0))
    {
        return cs;
    }
    
    // now determine one most likely side... caution heuristics 
    ox1 = f_obj2->cx() - f_obj1->right();
    ox1 = abs(ox1);
    ox2 = f_obj2->cx() - f_obj1->left();
    ox2 = abs(ox2);
    
    if (ox1 < ox2)
    {
        cs = RIGHT;
    }
    else
    {
        cs = LEFT;
        ox1 = ox2;
    }

    oy1 = f_obj2->cy() - f_obj1->top();
    oy1 = abs(oy1);
    oy2 = f_obj2->cy() - f_obj1->bottom();
    oy2 = abs(oy2);

    if (oy1 < oy2)
    {
        if (oy1 < ox1)
        {
            cs = TOP;
        }
    }
    else
    {
        if (oy2 < ox1)
        {
            cs = BOTTOM;
        }
    }

    return cs;
}
