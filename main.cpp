#include <iostream>
#include <string>

#include "SDL2/SDL.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

using namespace std;

SDL_Texture * LoadImage( std::string file )
{
    SDL_Surface *loadedImage = NULL;
    SDL_Texture *texture = NULL;

    loadedImage = SDL_LoadBMP( file.c_str() );
    if(loadedImage != NULL )
    {
        texture = SDL_CreateTextureFromSurface( renderer, loadedImage );
        SDL_FreeSurface( loadedImage );
    }
    else
        std::cout<<__FUNCTION__<< " Failed for file " << file << "with error: "<< SDL_GetError() << endl;

    return texture;
}

int main( int argc, char* args[] )
{
        //Start SDL
    SDL_Init( SDL_INIT_EVERYTHING );


    window = SDL_CreateWindow( "HellowWorld!", 100, 100, 640, 480, SDL_WINDOW_SHOWN );


    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );

    SDL_Texture *tex = NULL;
    tex = LoadImage( "res/helloworldies.bmp" );
    if( tex == NULL )
    {
        return 1;
    }

    SDL_RenderClear( renderer );
    SDL_RenderCopy( renderer, tex, NULL, NULL );
    SDL_RenderPresent( renderer );

    SDL_Delay( 2000 );

    //cleanup yo s
    SDL_DestroyTexture( tex );
    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );

    //Quit SDL
    SDL_Quit();

    return 0;
}
