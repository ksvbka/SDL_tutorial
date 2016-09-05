#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "Texture.h"

class Button {
  public:
    Button(SDL_Renderer* renderer, Texture* texture, int x = 0, int y = 0);

    ~Button();

    void setPosition(int x, int y);

    void render();

    void eventHandle(const SDL_Event &e);

  private:
    int x_;
    int y_;
    SDL_Renderer* renderer_;
    Texture* button_texture_;

    enum Spirte{
        MOUSE_OUT,
        MOUSE_OVER,
        MOUSE_DOWN,
        MOUSE_UP
    };

    Spirte currentSpirte_;
};


#endif


