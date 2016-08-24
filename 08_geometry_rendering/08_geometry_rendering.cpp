//Using SDL, SDL_image, standard IO, math, and strings
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cmath>
#include <iostream>
#include <stdexcept>

/*
    Using texture instead of SDL_Surfacce.
    SDL_Render -> SDL_BlitSurface or SDL_BlitScaled.
*/

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int ex_08_geometry_rendering() {
    /* Init SDL */
    if (SDL_Init(SDL_INIT_VIDEO) < 0 )
        throw std::runtime_error("Can not init SDL!");

    //Set texture filtering to linear
    if ( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        throw std::runtime_error("Warning: Linear texture filtering not enabled!");

    /* Init Window*/
    SDL_Window* window = SDL_CreateWindow("SDL Tutorial 08",
                                          SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT,
                                          SDL_WINDOW_SHOWN
                                         );
    if (!window)
        throw std::runtime_error("Can not create window");

    /* Create render for window*/
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
        throw std::runtime_error("Can not crate renderer!");
    SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

    /* Initialize PNG loading*/
    int imgFlags = IMG_INIT_PNG;
    if (!IMG_Init(imgFlags) & imgFlags)
        throw std::runtime_error("SDL_image could not initialize!");


    /*Main loop*/
    bool quit = false;

    //Event handler
    SDL_Event e;

    //While application is running
    while ( !quit ) {
        //Handle events on queue
        while ( SDL_PollEvent( &e ) != 0 ) {
            //User requests quit
            if ( e.type == SDL_QUIT ) {
                quit = true;
            }
        }

        //Clear screen
        // SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_SetRenderDrawColor( renderer, 0, 0, 0, 0xFF );
        SDL_RenderClear( renderer );

        //Render red filled quad
        SDL_Rect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
        SDL_SetRenderDrawColor( renderer, 0xFF, 0x00, 0x00, 0xFF );
        SDL_RenderFillRect( renderer, &fillRect );

        //Render green outlined quad
        SDL_Rect outlineRect = { SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6, SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 3 };
        SDL_SetRenderDrawColor( renderer, 0x00, 0xFF, 0x00, 0xFF );
        SDL_RenderDrawRect( renderer, &outlineRect );

        //Draw blue horizontal line
        SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0xFF, 0xFF );
        SDL_RenderDrawLine( renderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2 );

        //Draw vertical line of yellow dots
        SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0x00, 0xFF );
        for ( int i = 0; i < SCREEN_HEIGHT; i += 4 ) {
            SDL_RenderDrawPoint( renderer, SCREEN_WIDTH / 2, i );
        }

        //Update screen
        SDL_RenderPresent( renderer );
    }


    /*Free memory*/
    // SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    IMG_Quit();
    SDL_Quit();

    return 0;
}


int main(int argc, char const *argv[]) {
    try {
        ex_08_geometry_rendering();
    } catch (std::runtime_error &e) {
        std::cout << e.what() << std::endl;
    } catch (...) {
        std::cout << "..." << std::endl;
    }
    return 0;
}
