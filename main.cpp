#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Ventana.h"
#include "Objeto.h"

void cerrar()
{
    SDL_Quit();
}

SDL_Surface * superficie = NULL;
SDL_Texture * fondoVergas[2];

int main( int argc, char* argv[] )
{
    //Inicia SDL y SDL_image
    SDL_Init( SDL_INIT_VIDEO );
    IMG_Init( IMG_INIT_PNG );

    //Carga el fondo
    superficie = IMG_Load("naturaleza.jpg");

    //Camara
    SDL_Rect camara = { 0, 0, 440, 400 };

    bool mover = false;
    //Crea una ventana
    Ventana ventana1("Brickball", 440, 400 );
    Objeto muchacho("Sprites.png", &ventana1, 30, 30 );

    fondoVergas[0] = SDL_CreateTextureFromSurface(ventana1.obtenerSuperficie(), superficie);
    SDL_FreeSurface(superficie);

    if( !ventana1.fueCreada() );
    else
    {
        //Salir
        bool salir = false;
        SDL_Event evento;

        Uint32 inicio = 0;
        Uint32 tiempoTranscurrido;

        while(!salir){
            while( SDL_PollEvent( &evento ) != 0 ){
                if( evento.type == SDL_QUIT )
                    salir = true;
                if( evento.type == SDL_KEYDOWN ){
                    if( evento.key.keysym.sym == SDLK_RIGHT){
                        mover = true;
                    }
                }
                else if (evento.type == SDL_KEYUP){
                    muchacho.reset();
                    mover = false;
                }
            }

            ventana1.limpiar();

            tiempoTranscurrido = SDL_GetTicks() - inicio;
            if( mover && tiempoTranscurrido > 70 ) {
                camara.x += 12;
                if( camara.x + camara.w >= 1600 )
                {
                    camara.x = 0;
                }

                muchacho.cambiarSprite();
                inicio = SDL_GetTicks();
            }
            SDL_RenderCopy(ventana1.superficie, fondoVergas[0], &camara, NULL);
            muchacho.dibujar(ventana1.superficie);
            ventana1.actualizar();
        }
    }

    cerrar();

    return 0;
}
