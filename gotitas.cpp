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
    this->x = _x;
    setPos(this->x,550);
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

//Sprite de la gotita que recorre la imagen
void gotitas::sprite_gotita()
{   dx=0;
    dy+=50;//Varia dy porque la imagen de recorre hacia la derecha por esto es una sumatoria de posiciones
    if(dy >= 50*6)
    {
        dy=0;
    }
    this->update(-ancho/2,-alto/2,ancho,alto);//Actualizacion de la imagen
}
