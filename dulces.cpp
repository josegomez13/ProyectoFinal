#include "dulces.h"


bool Dulces::comprobarColision()
{
    if (this->posy>200) {
        return true;
    }

    return false;
}


void Dulces::caerDulceConstantement()
{
    this->posy=this->posy+this->velocidadCaida;
    actualizar();
}




void Dulces::actualizar()
{
    this->setPos(this->posx,this->posy);
}


Dulces::Dulces(float _posx, float _posy)
{
    srand(time(0));
    this->posx=_posx;
    this->posy=_posy;
    this->ancho = 20;
    this->alto  = 20;
    this->velocidadCaida = 1+ rand() % 6;
    std::cout << "DULCE --> x : "<<this->posx<< " y : " << this->posy << std::endl;
}



QRectF Dulces::boundingRect() const // BoundingRect, es donde se va a dibujar el personaje

{
    return QRectF(-ancho/2,-alto/2,ancho,alto);
}

void Dulces::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //painter->drawPixmap(-ancho/2,-alto/2,*pixmap,dy,dx,ancho,alto);
    //painter->drawRect(100,100,10,10);
    painter->drawRect(this->posx,this->posy,this->ancho,this->alto);
    //painter->drawEllipse(this->posx,this->posy,this->ancho,this->alto);

}


