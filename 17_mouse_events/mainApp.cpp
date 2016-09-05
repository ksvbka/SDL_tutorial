#include "Texture.h"
#include "Button.h"
#include <stdexcept>
#include <iostream>
#include <vector>


//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int Button_test() {
    /* Init SDL */
    if (SDL_Init(SDL_INIT_VIDEO) < 0 )
        throw std::runtime_error("Can not init SDL!");

    //Set texture filtering to linear
    if ( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        throw std::runtime_error("Warning: Linear texture filtering not enabled!");

    /* Init Window*/
    SDL_Window* window = SDL_CreateWindow("SDL Tutorial 17",
                                          SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT,
                                          SDL_WINDOW_SHOWN
                                         );
    if (!window)
        throw std::runtime_error("Can not create window");

    /* Initialize PNG loading*/
    int imgFlags = IMG_INIT_PNG;
    if (!IMG_Init(imgFlags) & imgFlags)
        throw std::runtime_error("SDL_image could not initialize!");

    /* Create render for window*/
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
        throw std::runtime_error("Can not create renderer!");
    SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

    Texture button_texture(renderer);
    button_texture.loadFromFile("button.png");

    std::vector<Button> vecButton{
        Button{renderer, &button_texture,   0,   0},     // Top left
        Button{renderer, &button_texture,   0, 280},   // Top right
        Button{renderer, &button_texture, 340,   0},   // Bottom left
        Button{renderer, &button_texture, 340, 280}  // Bottom right
    };

    /*Event handle*/
    SDL_Event e;
    bool quit = false;
    while (!quit) {
        while ( SDL_PollEvent(&e) != 0 ) {
            if (e.type == SDL_QUIT )
                quit = true;
            for(auto& button : vecButton)
                button.eventHandle(e);
        }

        //Update screen
            for(auto& button : vecButton)
                button.render();
        SDL_RenderPresent( renderer );
    }


    /*Free memory*/
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    IMG_Quit();
    SDL_Quit();

    return 0;
}

int main(int argc, char const *argv[])
{
    try{
        Button_test();
    }catch(std::runtime_error &e){
        std::cout << e.what() << std::endl;
    }catch(...){
        std::cout << "..." << std::endl;
    }
    return 0;
}
