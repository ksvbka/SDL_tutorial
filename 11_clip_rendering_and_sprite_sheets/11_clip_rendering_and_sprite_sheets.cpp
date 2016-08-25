#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
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

    void render(int x, int y, SDL_Rect* clip = nullptr);

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

void Texture::render(int x, int y, SDL_Rect* clip) {
    SDL_Rect renderQuad = {x, y, width_, height_};
    //Set clip rendering dimensions
    if ( clip != nullptr ) {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    SDL_RenderCopy(renderer_, texture_, clip , &renderQuad);
}

int ex_11_clip_rendering_and_sprite_sheets() {
    /* Init SDL */
    if (SDL_Init(SDL_INIT_VIDEO) < 0 )
        throw std::runtime_error("Can not init SDL!");

    //Set texture filtering to linear
    if ( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        throw std::runtime_error("Warning: Linear texture filtering not enabled!");

    /* Init Window*/
    SDL_Window* window = SDL_CreateWindow("SDL Tutorial 11",
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

    Texture spriteSheetTexture{renderer};
    if (!spriteSheetTexture.loadFromFile("dots.png"))
        throw std::runtime_error("Failed to load image");

    /* Vector SDL_Rect include positon for each sprite of spriteSheet */
    std::vector<SDL_Rect> spriteSheet {
        {  0,  0, 100, 100}, // Top left
        {100,  0, 100, 100}, // Top right
        {100,  0, 100, 100}, // Bottom left
        {100, 100, 100, 100} // Bottom right
    };

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

        spriteSheetTexture.render(0, 0, &spriteSheet[0]);
        spriteSheetTexture.render(SCREEN_WIDTH - spriteSheet[1].w, 0, &spriteSheet[1]);
        spriteSheetTexture.render(0, SCREEN_HEIGHT - spriteSheet[2].h, &spriteSheet[2]);
        spriteSheetTexture.render(SCREEN_WIDTH - spriteSheet[3].w, SCREEN_HEIGHT - spriteSheet[3].h, &spriteSheet[3]);


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
        ex_11_clip_rendering_and_sprite_sheets();
    } catch (std::runtime_error &e) {
        std::cout << e.what() << std::endl;
    } catch (...) {
        std::cout << "..." << std::endl;
    }
    return 0;
}
