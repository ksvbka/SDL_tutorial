#ifndef __BALL_H__
#define __BALL_H__

#include "Entity.h"

// Define a ball speed in pixels per milisecond;
const float BALL_SPEED = 0.1;

class Ball : public Entity {
  public:
    Ball(SDL_Renderer* renderer);

    virtual ~Ball();

    void update(Uint32 dt);

    void render();

    void setDirection(float dirx, float diry);

    float dirx() { return dirx_;}
    float diry() { return diry_;}


  private:
    float dirx_;
    float diry_;
    SDL_Texture* texture_;
};
#endif
