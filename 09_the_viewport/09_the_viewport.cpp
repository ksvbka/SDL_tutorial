#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdexcept>
#include <iostream>

/*
    Using texture instead of SDL_Surfacce.
    SDL_Render -> SDL_BlitSurface or SDL_BlitScaled.
*/

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Loads individual image as texture
SDL_Texture* LoadTexture(std::string path, SDL_Renderer* renderer);

int ex_09_viewport() {
	/* Init SDL */
	if (SDL_Init(SDL_INIT_VIDEO) < 0 )
		throw std::runtime_error("Can not init SDL!");

	//Set texture filtering to linear
	if ( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		throw std::runtime_error("Warning: Linear texture filtering not enabled!");

	/* Init Window*/
	SDL_Window* window = SDL_CreateWindow("SDL Tutorial 09",
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


	/* Load image */
	SDL_Texture* texture = LoadTexture("ghost-rider.png", renderer);


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
		SDL_RenderClear( renderer );

		/* Top left corner viewport*/
		SDL_Rect topLeftViewport = {0, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
		SDL_RenderSetViewport(renderer, &topLeftViewport);
		SDL_RenderCopy(renderer, texture, 0, 0);


		/* Top right viewport */
		SDL_Rect topRightViewport = {SCREEN_WIDTH / 2, 0,SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
		SDL_RenderSetViewport(renderer, &topRightViewport);
		SDL_RenderCopy(renderer, texture, 0, 0);

		/* Bottom viewport */
		SDL_Rect bottomViewport = {0, SCREEN_HEIGHT/2 , SCREEN_WIDTH , SCREEN_HEIGHT / 2};
		SDL_RenderSetViewport(renderer, &bottomViewport);
		SDL_RenderCopy(renderer, texture, 0, 0);

		//Update screen
		SDL_RenderPresent( renderer );
	}


	/*Free memory*/
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	IMG_Quit();
	SDL_Quit();

	return 0;
}


int main(int argc, char const *argv[]) {
	try {
		ex_09_viewport();
	} catch (std::runtime_error &e) {
		std::cout << e.what() << std::endl;
	} catch (...) {
		std::cout << "..." << std::endl;
	}
	return 0;
}


//Loads individual image as texture
SDL_Texture* LoadTexture(std::string path, SDL_Renderer* renderer) {
	SDL_Surface* img_surface = IMG_Load(path.c_str());
	if (!img_surface)
		throw std::runtime_error("Canot load img");
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, img_surface);
	if (!texture)
		throw std::runtime_error("Unable to create texture");

	SDL_FreeSurface(img_surface);
	return texture;
}
