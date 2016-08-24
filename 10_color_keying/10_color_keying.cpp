#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include <stdexcept>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

class Texture {
  public:
    Texture(SDL_Renderer* renderer)
        : texture_{nullptr}, renderer_{renderer}, width_{}, height_{}
    {}

    ~Texture() { free();}

    bool loadFromFile(std::string path);

    void render(int x, int y);

    void free();

    int width() { return width_;}

    int height() { return height_;}

  private:
    SDL_Texture*  texture_;
    SDL_Renderer* renderer_;
    int     width_;
    int     height_;
};

bool Texture::loadFromFile(std::string path) {
    //Get rid of preexisting texture
    free();

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (!loadedSurface)
        throw std::runtime_error("Can't load image");

    /*Color key image*/
    SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
    texture_ = SDL_CreateTextureFromSurface(renderer_, loadedSurface);
    width_ = loadedSurface->w;
    height_ = loadedSurface->h;

    SDL_FreeSurface(loadedSurface);

    return (texture_ != nullptr);
}

void Texture::free() {
    if (texture_ != nullptr) {
        SDL_DestroyTexture( texture_ );
        texture_ = nullptr;
        width_ = 0;
        height_ = 0;
    }
}

void Texture::render(int x, int y) {
    SDL_Rect renderQuad = {x, y, width_, height_};
    SDL_RenderCopy(renderer_, texture_, 0, &renderQuad);
}

int ex_10_color_keying() {
    /* Init SDL */
    if (SDL_Init(SDL_INIT_VIDEO) < 0 )
        throw std::runtime_error("Can not init SDL!");

    //Set texture filtering to linear
    if ( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        throw std::runtime_error("Warning: Linear texture filtering not enabled!");

    /* Init Window*/
    SDL_Window* window = SDL_CreateWindow("SDL Tutorial 10",
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


    /*Load texture*/

    Texture backgroundTexture{renderer};
    if (!backgroundTexture.loadFromFile("background.png"))
        throw std::runtime_error("Failed to load background");

    Texture fooTexture{renderer};
    if (!fooTexture.loadFromFile("foo.png"))
        throw std::runtime_error("Failed to load foo texture image");

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
        SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( renderer );

        backgroundTexture.render(0,0);
        fooTexture.render(240,190);

        //Update screen
        SDL_RenderPresent( renderer );
    }


    /*Free memory*/
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    IMG_Quit();
    SDL_Quit();

    return 0;
}

int main(int argc, char const *argv[]) {
    try {
        ex_10_color_keying();
    } catch (std::runtime_error &e) {
        std::cout << e.what() << std::endl;
    } catch (...) {
        std::cout << "..." << std::endl;
    }
    return 0;
}
