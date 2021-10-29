#include "vida.h"

//Retorna la posicion en y de la vida

int Vida::getPosy() const
{
    return posy;
}
//Actualiza el valor de la posicion en y de la vida
void Vida::setPosy(int value)
{
    posy = value;
}
// Boundingrect, es donde se va a dibujar a la gotita
QRectF Vida::boundingRect() const
{
    return QRectF(-ancho/2,-alto/2,ancho,alto);
}

//Paint dibuja a la frutaburbuja ,su imagen ,altura, ancho y largo
void Vida::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-ancho/2,-alto/2,*pixmapVidaAgua,dx,dy,ancho,alto);
}
//Retorna la posicion en x de la vida
int Vida::getPosx() const
{
    return posx;
}
//Actualiza el valor de la posicion en x de la vida
void Vida::setPosx(int value)
{
    posx = value;
}

Vida::Vida(int x, int y)
{
    //Posicion en x y y de la vida
    this->posx=x;
    this->posy=y;
    this->dx = 0;
    this->dy =0;
    this->pixmapVidaAgua=new QPixmap(":/Backgrounds games/gotica.png");
    //Ancho y alto de la imagen
    this->ancho=50;
    this->alto=50;
    setPos(posx,posy);

}
