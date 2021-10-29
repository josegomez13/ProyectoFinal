#include "gotitas.h"

//Retorna el valor de la posicion de la frutaburbuja en el eje x
int gotitas::getPosx() const
{
    return posx;
}
//Actualiza el valor de la posicion del personaje en el eje x
void gotitas::setPosx(int value)
{
    posx = value;
}
//Retorna el valor de la posicion de la frutaburbuja en el eje y
int gotitas::getPosy() const
{
    return posy;
}
//Actualiza el valor de la posicion de la frutaburbuja en el eje y
void gotitas::setPosy(int value)
{
    posy = value;
}
gotitas::gotitas(int _x)
{
    pixmap = new QPixmap(":/Backgrounds games/gotica.png");
    dy =0;
    ancho = 50;//Ancho del pixmap
    alto=50;//Alto del pixmap
    this->posx = _x;
    setPos(this->posx,550);
}


// Boundingrect, es donde se va a dibujar a la gota
QRectF gotitas::boundingRect() const
{
    return QRectF(-ancho/2,-alto/2,ancho,alto);
}
//Paint dibuja a la gota, su imagen, altura, ancho y largo
void gotitas::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-ancho/2,-alto/2,*pixmap,dy,0,ancho,alto);
}

