#ifndef OBJETO_H
#define OBJETO_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "Ventana.h"

class Objeto
{
    friend int main( int argc, char* argv[] );
    friend bool coaliciona(Objeto *, Objeto *);
    friend void establecerVelocidad( Objeto * a, Objeto * b );

    public:
        //Constructor
        Objeto( std::string, Ventana*, int, int );

        //Destructor
        ~Objeto();

        //Asigna el sprite
        void asignarSprite( std::string, Ventana* );

        //Elimina el sprite
        void destruirSprite();

        //Coaliciona
        void coaliciona();

        //
        void cambiarSprite();

        void reset();

        //Mueve la "pelota"
        void mover();

        //Dibuja en pantalla
        void dibujar( SDL_Renderer * );

    private:
        SDL_Texture* imagen;
        SDL_Rect sprite;

        int x;
        int y;
        int w;
        int h;
        int velocidadX;
        int velocidadY;
};

Objeto::Objeto( std::string directorio, Ventana* ventana, int x, int y )
{
    //Asigna el sprite
    asignarSprite( directorio, ventana );

    //Inicializa los dem�s par�metros
    this -> x = x;
    this -> y = 250;

    sprite.x = 15;
    sprite.y = 150;
    sprite.w = 70;
    sprite.h = 100;

    //Inicializa la velocidad
    velocidadX = 6;
    velocidadY = 1;
}

Objeto::~Objeto()
{
    destruirSprite();
    x = 0;
    y = 0;
}

void Objeto::asignarSprite( std::string directorio, Ventana * ventana )
{
    SDL_Surface* superficie = IMG_Load( directorio.c_str() );
    if( superficie != NULL )
    {
        SDL_SetColorKey(superficie, SDL_TRUE, SDL_MapRGB(superficie->format, 0x00, 0x00, 0x00));
        imagen = SDL_CreateTextureFromSurface( ventana -> obtenerSuperficie(), superficie );
        h = superficie -> h;
        w = superficie -> w;
        SDL_FreeSurface(superficie);
    }
    else
    {
        imagen = NULL;
    }
}

void Objeto::cambiarSprite()
{
    if(sprite.x + sprite.w <= w - sprite.w )
    {
        sprite.x += 70;
    }
    else
    {
        sprite.x = 15;
    }
}

void Objeto::reset()
{
    sprite.x = 15;
}

void Objeto::destruirSprite()
{
    if( imagen != NULL )
    {
        SDL_DestroyTexture(imagen);
        imagen = NULL;
        h = 0;
        w = 0;
    }
}

void Objeto::coaliciona()
{
    if( x < 0 || x + w  > 440 )
    {
        if( x < 0 )
            x = 0;
        else
            x = 440 - w;

        velocidadX *= -1;
    }

    if( y < 0 || y + h > 400 )
    {
        if( y < 0 )
            y = 0;
        else
            y = 400 - h;

        velocidadY *= -1;
    }
}

void Objeto::mover()
{
    x += velocidadX;
}

void Objeto::dibujar( SDL_Renderer * superficie )
{
    SDL_Rect quad = { x, y, sprite.w, sprite.h };
    SDL_RenderCopy( superficie, imagen, &sprite, &quad );
}

bool coaliciona( Objeto * a, Objeto * b )
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a->x;
    rightA = a->x + a->w;
    topA = a->y;
    bottomA = a->y + a->h;

    //Calculate the sides of rect B
    leftB = b->x;
    rightB = b->x + b->w;
    topB = b->y;
    bottomB = b->y + b->h;

    //If any of the sides from A are outside of B
    if( bottomA < topB )
    {
        return false;
    }

    if( topA > bottomB )
    {
        return false;
    }

    if( rightA < leftB )
    {
        return false;
    }

    if( leftA > rightB )
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}

void establecerVelocidad( Objeto * a, Objeto * b )
{
    printf("XA = %d, XB = %d\nYA = %d, YB = %d\n", a -> x, b -> x, a -> y, b -> y);
     int diferenciaX = (a -> x + a -> w) - b -> x;
    int diferenciaY = (a -> y + a -> h) - b -> y;

    if( b -> x < a -> x && b -> y < a -> y )
    {
        diferenciaX = (b -> x + b -> w) - a -> x;
    }

    if( diferenciaX > diferenciaY )
    {
        a -> velocidadY *= -1;
        b -> velocidadY *= -1;
    }
    else if( diferenciaX < diferenciaY )
    {
        a -> velocidadX *= -1;
        b -> velocidadX *= -1;
    }
    else if( diferenciaX == diferenciaY )
    {
        a -> velocidadX *= -1;
        b -> velocidadX *= -1;
        a -> velocidadY *= -1;
        b -> velocidadY *= -1;
    }
}

#endif // PELOTA_H
