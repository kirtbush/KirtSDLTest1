#include <iostream>
#include <string>
#include <stdexcept>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

using namespace std;

SDL_Texture * LoadImage( std::string file )
{
    SDL_Texture *texture = NULL;

    texture = IMG_LoadTexture(renderer, file.c_str());
    if( texture == NULL )
    {
        throw std::runtime_error("Failed to load image: " + file + IMG_GetError());
    }

    return texture;
}

void ApplySurface( int x, int y, SDL_Texture *tex, SDL_Renderer *rend )
{
    SDL_Rect pos;
    pos.x = x;
    pos.y = y;
    SDL_QueryTexture( tex, NULL, NULL, &pos.w, &pos.h );
    SDL_RenderCopy( rend, tex, NULL, &pos );
}

int main( int argc, char* args[] )
{
        //Start SDL
    if ( SDL_Init( SDL_INIT_EVERYTHING ) == -1)
    {
        return 1;
    }

    window = SDL_CreateWindow( "HelloWorld!", SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );

    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );

    SDL_Texture *background = NULL, *face = NULL;
    background = LoadImage( "res/background.bmp" );
    if( background == NULL )
    {
        return 2;
    }

    face = LoadImage( "res/face.bmp" );
    if( face == NULL )
    {
        return 3;
    }

    SDL_RenderClear( renderer );

    int bW, bH;
    SDL_QueryTexture(background, NULL, NULL, &bW, &bH);
    for(int idx=0; idx < 2; idx++ )
        for(int idy=0; idy < 2; idy++ )
            ApplySurface( idx * bW, idy * bH, background, renderer );

    int fW, fH;
    SDL_QueryTexture(face, NULL, NULL, &fW, &fH);
    int x = SCREEN_WIDTH / 2 - fW / 2;
    int y = SCREEN_HEIGHT / 2 - fH / 2;
    ApplySurface(x, y, face, renderer);

    SDL_RenderPresent( renderer );

    SDL_Delay( 2000 );

    //cleanup yo s
    SDL_DestroyTexture( background );
    SDL_DestroyTexture( face );
    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );

    //Quit SDL
    SDL_Quit();

    return 0;
}
