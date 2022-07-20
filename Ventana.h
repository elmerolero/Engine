#ifndef VENTANA_H
#define VENTANA_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>

class Ventana
{
    public:
        //Constructor sin inicializar
        Ventana( std::string, int largo, int alto );

        //Destructor
        ~Ventana();

        //Crea la ventana
        void crearVentana();

        //Destruye la ventana y libera memoria
        void destruirVentana();

        //Obtiene la superficie que a la que hay que dibujar
        SDL_Renderer * obtenerSuperficie();

        //Devuelve positivo si la ventana fue creada correctamente
        bool fueCreada();

        //Limpia la pantalla
        void limpiar();

        //Actualiza la pantalla
        void actualizar();

        //Superficie sobre la que dibuja
        SDL_Renderer * superficie;

    private:
        SDL_Window * ventana;

        std::string titulo;
        int largo;
        int alto;
};

Ventana::Ventana( std::string titulo, int largo, int alto )
{
    //Asigna el t�tulo
    this -> titulo = titulo;

    //Asigna el largo de la ventana
    this -> largo = largo;

    //Asigna el alto
    this -> alto = alto;

    //Crea la ventana
    crearVentana();
}

Ventana::~Ventana()
{
    largo = 0;
    alto = 0;

    destruirVentana();
}

void Ventana::crearVentana()
{
    //Crea la ventana
    ventana = SDL_CreateWindow( titulo.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this -> largo, this -> alto, SDL_WINDOW_SHOWN );
    if( ventana == NULL )
    {
        printf("No se cre� la ventana. Error: %s", SDL_GetError() );
    }
    else
    {
        //Crea la superficie
        superficie = SDL_CreateRenderer( ventana, -1, SDL_RENDERER_ACCELERATED );
        if( superficie == NULL )
        {
            printf("No se cre� la superficie. Error: %s", SDL_GetError() );
        }
        else
        {
            //Establece el color de la superficie en blanco
            SDL_SetRenderDrawColor( superficie, 0xFF, 0xFF, 0xFF, 0xFF);
        }
    }
}

void Ventana::destruirVentana()
{
    //Miembros en cero
    largo = 0;
    alto = 0;

    //Destruye la superficie
    SDL_DestroyRenderer( superficie );

    //Destruye la ventana
    SDL_DestroyWindow( ventana );

    //Establece en NULL
    superficie = NULL;
    ventana = NULL;
}

bool Ventana::fueCreada()
{
    return ventana != NULL && superficie != NULL;
}

SDL_Renderer * Ventana::obtenerSuperficie()
{
    return superficie;
}

void Ventana::limpiar()
{
    SDL_SetRenderDrawColor( superficie, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear( superficie );
}

void Ventana::actualizar()
{
    SDL_RenderPresent( superficie );
}

#endif // VENTANA_H
