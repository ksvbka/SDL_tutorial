#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Entity
{
public:
    Entity(SDL_Renderer* renderer) : renderer_{renderer}
    {}

    virtual ~Entity() { };

    virtual void update(Uint32 dt) = 0;

    virtual void render() = 0;

    virtual bool collides(Entity* other);

    float x()     { return x_;}
    float y()     { return y_;}
    float width() { return width_;}
    float height() { return height_;}

    void setPosition(float x, float y){
        x_ = x;
        y_ = y;
    }

    protected:
        SDL_Renderer* renderer_;
        float x_,y_,width_,height_;
};


#endif //__ENTITY_H__


