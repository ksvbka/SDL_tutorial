#include "Game.h"
#include <stdexcept>

Game::Game() {
    window_ = nullptr;
    renderer_ = nullptr;
    quit_ = false;
}

Game::~Game() {
    clean();
}

void Game::init() {
    /* Init SDL */
    if (SDL_Init(SDL_INIT_VIDEO) < 0 )
        throw std::runtime_error("Can not init SDL!");

    //Set texture filtering to linear
    if ( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        throw std::runtime_error("Warning: Linear texture filtering not enabled!");

    /* Init Window*/
    window_ = SDL_CreateWindow("SDL Tutorial 07",
                               SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                               SCREEN_WIDTH, SCREEN_HEIGHT,
                               SDL_WINDOW_SHOWN
                              );
    if (!window_)
        throw std::runtime_error("Can not create window");

    /* Create render for window*/
    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer_)
        throw std::runtime_error("Can not create renderer!");
    SDL_SetRenderDrawColor( renderer_, 0, 0, 0, 0xFF );

    /* Initialize PNG loading*/
    int imgFlags = IMG_INIT_PNG;
    if (!IMG_Init(imgFlags) & imgFlags)
        throw std::runtime_error("SDL_image could not initialize!");
}

void Game::clean() {
    // Clean renderer and window
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);

    IMG_Quit();
    SDL_Quit();
}

void Game::handleEvent() {
    while ( SDL_PollEvent( &event_ ) != 0 ) {
        //User requests quit
        if ( event_.type == SDL_QUIT ) {
            quit_ = true;
        }
    }
}

void Game::update(Uint32 dt) {
    ball_->update(dt);
}


void Game::run() {
    /*Create Item*/
    ball_  = new Ball(renderer_);

    /*Main loop*/
    Uint32 frame_time = SDL_GetTicks();

    while (!quit_) {
        handleEvent();
        update(FRAME_TICKS);
        render();

        if (SDL_GetTicks() - frame_time < FRAME_TICKS)
            SDL_Delay(FRAME_TICKS - (SDL_GetTicks() - frame_time));
    }

    delete ball_;
}

void Game::render() {
    //Clear screen
    SDL_RenderClear( renderer_ );

    //Render item's texture to screen
    ball_->render();

    //Update screen
    SDL_RenderPresent( renderer_ );
}


