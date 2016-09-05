#include "Ball.h"
#include <cmath>

Ball::Ball(SDL_Renderer* renderer) : Entity(renderer) {

    SDL_Surface* loaded_image = IMG_Load("image/ball.png");
    texture_ = SDL_CreateTextureFromSurface(renderer, loaded_image);
    SDL_FreeSurface(loaded_image);

    x_ = 0;
    y_ = 0;
    width_ = 24;
    height_ = 24;

    /* Init direction */
    setDirection(1, 1);
}

Ball::~Ball() {
    SDL_DestroyTexture(texture_);
}

void Ball::setDirection(float dirx, float diry){
    // Normalize the direction vector and multiply with BALL_SPEED
    float length = sqrt(dirx * dirx + diry * diry);

    dirx_ = dirx / length;
    diry_ = diry / length;
}

void Ball::render() {
    SDL_Rect rect;
    rect.x = (int)(x_ + 0.5f); // Round the float to the nearest integer
    rect.y = (int)(y_ + 0.5f); // Round the float to the nearest integer
    rect.w = width_;
    rect.h = height_;
    SDL_RenderCopy(renderer_, texture_, 0, &rect);
}

void Ball::update(Uint32 dt){
    x_ += dirx_ * BALL_SPEED * dt;
    y_ += diry_ * BALL_SPEED* dt;

    if(x_ <=0 || x_ >= 800)
        dirx_ = -dirx_;
    if(y_ <= 0 || y_ >= 600)
        diry_ = -diry_;
}
