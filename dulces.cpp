#include "dulces.h"
#include <math.h>
#include <cmath>
#include<QDebug>

bool Dulces::comprobarColision() // funcion que retorna un booleano cuando el dulce toque el limite de la pantalla
{
    if (this->posy>880) {
        return true;
    }

    return false;
}


void Dulces::caerDulceConstantement() // funcion que para la caida de los dulces
{
    this->posy=this->posy+this->velocidadCaida; // ecuacion para que a la posicion en 'y' se le sume cierta velocidad random
    actualizar(); // actualiza la posicion en 'y' a la caida de un dulce
}


void Dulces::actualizar() //actualiza la posicion en 'x' y 'y' del dulce
{
    this->setPos(this->posx,this->posy);
}


Dulces::Dulces(float _posx, float _posy)
{
    srand(time(0));
    this->posx=_posx;
    this->posy=_posy;
    this->ancho = 40;
    this->alto  = 40;
    this->dx =0;
    this->dy =0;
    this->velocidadCaida = 1 + rand() % 6;
    this->pixmap=new QPixmap(":/Backgrounds games/dulces.png");//direccion del sprite

}

QRectF Dulces::boundingRect() const // BoundingRect, es donde se va a dibujar el personaje en la escena

{
    return QRectF(-ancho/2,-alto/2,ancho,alto);
                  //se divide entre 2 para ubicar el centro
}

void Dulces::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-ancho/2,-alto/2,*pixmap,dy,dx,ancho,alto);

}


