#include <SDL2/SDL.h>
#include <stdexcept>
#include <iostream>

/*
Key of this programe 2 funciton:
1. SDL_Convert(SDL_Surface* , format, 0);

2.
    SDL_Rect stretchRect{0,0,SCREEN_WIDTH,SCREEN_HIGHT};
    SDL_BlitScaled(image, nullptr, screen_surface, &stretchRect);

*/


int const SCREEN_WIDTH = 640;
int const SCREEN_HIGHT = 480;

/*Function Load image */
SDL_Surface* LoadSurface(std::string path){
    SDL_Surface* image = SDL_LoadBMP(path.c_str());
        if(!image) throw std::runtime_error("Can't load image");
    return image;
}

/* Optimized */
SDL_Surface* OptimizedSurface(std::string path, SDL_Surface* screen_surface){
    SDL_Surface* image = LoadSurface(path);
    SDL_Surface* optimizedSurface = SDL_ConvertSurface(image, screen_surface->format, 0);
    if(!optimizedSurface)
        throw std::runtime_error("Unable to optimize image at" + path);
    SDL_FreeSurface(image);

    return optimizedSurface;
}


int ex5_optimized_surface_loading_and_soft_stretching() {
    /* Init SDL */
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
        throw std::runtime_error("Can't int sdl");

    /* Create Window*/
    SDL_Window* window = SDL_CreateWindow("SDL Tutorial 05",
                            SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,
                            SCREEN_WIDTH, SCREEN_HIGHT,
                            SDL_WINDOW_SHOWN
                        );

    if(window == nullptr)
        throw std::runtime_error("Can't create window");
    SDL_Surface* screen_surface = SDL_GetWindowSurface(window);

    /* Load bpm image and optimized*/
    SDL_Surface* image = OptimizedSurface("stretch.bmp", screen_surface);
    if(image == nullptr)
        throw std::runtime_error("Can't load image");

    SDL_Event e;
    bool quit = false;

    while ( !quit ) {
        // Handle event on queue
        while ( SDL_PollEvent(&e) != 0 ) {
            if (e.type == SDL_QUIT )
                quit = true;
        }
        /* Display image to window */
        //SDL_BlitSurface(image, nullptr, screen_surface, nullptr);

        /* Display stretched window */
        SDL_Rect stretchRect{0,0,SCREEN_WIDTH,SCREEN_HIGHT};
        SDL_BlitScaled(image, nullptr, screen_surface, &stretchRect);

        SDL_UpdateWindowSurface(window);
    }

    /* Free memory and close window */

    SDL_FreeSurface(image);
    SDL_DestroyWindow(window);
    SDL_Quit();


    return 0;
}

int main(int argc, char const *argv[])
{
    try{
        ex5_optimized_surface_loading_and_soft_stretching();
    }catch(std::runtime_error& e){
        std::cout << e.what() << std::endl;
    }catch(...){
        std::cout << "WTF?" << std::endl;
    }
    return 0;
}

