#include "Texture.h"
#include <stdexcept>

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

void Texture::setColor(Uint8 red, Uint8 green, Uint8 blue){
        //Modulate texture rgb
    SDL_SetTextureColorMod( texture_, red, green, blue );
}

void Texture::setAlpha(Uint8 alpha) {
        //Modulate texture alpha
    SDL_SetTextureAlphaMod( texture_, alpha );
}


void Texture::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, width_, height_ };

    //Set clip rendering dimensions
    if( clip != NULL )
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    //Render to screen
    SDL_RenderCopyEx( renderer_, texture_, clip, &renderQuad, angle, center, flip );
}
