#ifndef __GAME_H__
#define __GAME_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Ball.h"

#include <vector>

//Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

const Uint32 FRAME_TICKS = 16; // ~ 60FPS

class Game {
  public:
    Game();
    virtual ~Game();

    void init();

    virtual void run();

  private:
    SDL_Window* window_;
    SDL_Renderer* renderer_;
    SDL_Event event_;
    bool quit_;

    Ball* ball_;

    virtual void handleEvent();
    virtual void update(Uint32 dt);
    virtual void render();
    virtual void clean();

    virtual void newGame() {};

};

#endif
