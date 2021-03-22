//
//  collision.hpp
//  SDL_Pong
//

#ifndef collision_hpp
#define collision_hpp

#include "graphicsobject.hpp"

enum CollisionType
{
    NONE = 0x0,
    TOP = 0x1,
    BOTTOM = 0x2,
    LEFT = 0x4,
    RIGHT = 0x8
};


CollisionType checkCollision(const GraphicsObject* f_obj1, const GraphicsObject* f_obj2);

#endif /* collision_hpp */
