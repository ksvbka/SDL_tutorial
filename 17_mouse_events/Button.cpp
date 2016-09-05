#include "Button.h"

// Spirte's position of mouse
SDL_Rect SpirteRect[4] = {
    {0,   0, 300, 200}, // MOUSE_OUT
    {0, 200, 300, 200}, // MOUSE_OVER
    {0, 400, 300, 200}, // MOUSE_DOWN
    {0, 600, 300, 200}, // MOUSE_UP
};

const int BUTTON_WIDTH = 300;
const int BUTTON_HEIGHT = 200;

Button::Button(SDL_Renderer* renderer, Texture* texture, int x, int y)
    : renderer_{renderer}, button_texture_{texture}, x_{x}, y_{y} {
    currentSpirte_ = MOUSE_OUT;
}

Button::~Button() {
    button_texture_ = nullptr;
}

void Button::setPosition(int x, int y) {
    x_ = x;
    y_ = y;
}

void Button::render() {
    button_texture_->render(x_, y_, &SpirteRect[currentSpirte_]);
}

void Button::eventHandle(const SDL_Event& e) {
    if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP) {
        /* Get mouse position */
        int x, y;
        SDL_GetMouseState(&x, &y);
        /*Mose over*/
        if ( x_ <= x && x <= x_ + BUTTON_WIDTH  &&
             y_ <= y && y <= y_ + BUTTON_HEIGHT )
        {

            switch (e.type) {
            case SDL_MOUSEMOTION:
                currentSpirte_ = MOUSE_OVER;
                break;
            case SDL_MOUSEBUTTONUP:
                currentSpirte_ = MOUSE_UP;
                break;
            case SDL_MOUSEBUTTONDOWN:
                currentSpirte_ = MOUSE_DOWN;
                break;
            }
        }

        else {
            currentSpirte_ = MOUSE_OUT;
        }

    }

}
