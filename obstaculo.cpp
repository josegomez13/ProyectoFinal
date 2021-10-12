#include "obstaculo.h"

obstaculo::obstaculo()
{

}

obstaculo::obstaculo(int x, int y, int w, int h)
{
    this->posx=x;
    this->posy=y;
    this->w=w;
    this->h=h;
    setPos(posx, posy); //posición donde se va a ubicar
}

QRectF obstaculo::boundingRect() const
{
    return QRectF(posx,posy,w,h);
}

void obstaculo::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::green);
    painter->drawRect(boundingRect());
}


