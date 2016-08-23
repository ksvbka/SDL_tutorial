#include <SDL2/SDL.h>
#include <iostream>
#include <stdexcept>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int ex_03_event_driven_programming()
{
    /* Init SDL */
    if (SDL_Init(SDL_INIT_VIDEO) < 0 )
        throw std::runtime_error("Can not init SDL!");

    /* Init Window and surface */
    SDL_Window* window = SDL_CreateWindow("SDL Tutorial 02",
                                        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if (!window)
        throw std::runtime_error("Can not create window");

    /* Get window surface from SDL_window window*/
    SDL_Surface* screen_surface = SDL_GetWindowSurface(window);

    /* Load bmp image to surface */
    SDL_Surface* img_surface = SDL_LoadBMP("hello_world.bmp");
    if(!screen_surface)
        throw std::runtime_error("Canot load img");

    SDL_Event e;
    bool quit = false;

    while ( !quit ) {
        // Handle event on queue
        while ( SDL_PollEvent(&e) != 0 ) {
            if (e.type == SDL_QUIT )
                quit = true;
        }
        /* Display image to window */
        SDL_BlitSurface(img_surface, nullptr, screen_surface, nullptr);
        SDL_UpdateWindowSurface(window);
    }

    /* Free memory and close window */

    SDL_FreeSurface(img_surface);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

int main(int argc, char const *argv[])
{
    try{
        ex_03_event_driven_programming();
    }catch(std::runtime_error &e){
        std::cout << e.what() << std::endl;
    }catch(...){
        std::cout << "..." << std::endl;
    }
    return 0;
}
