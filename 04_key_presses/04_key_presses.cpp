#include <SDL2/SDL.h>
#include <iostream>
#include <vector>


const int WINDOW_WIDTH = 640;
const int WINDOW_HIGHT  = 480;

SDL_Surface* LoadImage(std::string path){
    SDL_Surface* buf = SDL_LoadBMP(path.c_str());
    if(!buf)
        std::cout << "Can't load image in path: "+ path << std::endl;
    return buf;
}

int main(int argc, char const *argv[]) {
    /* Init code */
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        std::cout << "Failed to init SDL" << std::endl;
        return 0;
    }

    /* Create Window and window surface */
    SDL_Window* window = SDL_CreateWindow("04 key present", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HIGHT, SDL_WINDOW_SHOWN);
    if ( !window ) {
        std::cout << "Can't create window" << std::endl;
        return 0;
    }
    SDL_Surface* windowSurface = SDL_GetWindowSurface(window);

    /* Load image to an vector */
    std::vector<SDL_Surface* > img_data;
    SDL_Surface* currentSurface;

    img_data.push_back(LoadImage("press.bmp"));
    img_data.push_back(LoadImage("up.bmp"));
    img_data.push_back(LoadImage("down.bmp"));
    img_data.push_back(LoadImage("left.bmp"));
    img_data.push_back(LoadImage("right.bmp"));

    /* Event handle */
    SDL_Event e;
    bool quit = false;

    enum KeyEvent{
        KEY_DEFAULT,
        KEY_UP,
        KEY_DOWN,
        KEY_LEFT,
        KEY_RIGHT
    };

    while(!quit){
        /* Process event in queue */
        while(SDL_PollEvent(&e) != 0){
            if (e.type == SDL_QUIT){
                quit = true;
            }else{
                switch(e.key.keysym.sym){
                    case SDLK_UP:
                        currentSurface = img_data[KEY_UP];
                        break;
                    case SDLK_DOWN:
                        currentSurface = img_data[KEY_DOWN];
                        break;
                    case SDLK_LEFT:
                        currentSurface = img_data[KEY_LEFT];
                        break;
                    case SDLK_RIGHT:
                        currentSurface = img_data[KEY_RIGHT];
                        break;
                    default:
                        currentSurface = img_data[KEY_DEFAULT];
                }

                /* Apply surface */
                SDL_BlitSurface(currentSurface, nullptr, windowSurface, nullptr);

                /* Display to screen */
                SDL_UpdateWindowSurface(window);

            }
        }
    }

    /* Free memory */
    for(auto& elem : img_data)
        SDL_FreeSurface(elem);

    /* Detroy window */
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
