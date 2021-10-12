#ifndef OBSTACULO_H
#define OBSTACULO_H
#include <QGraphicsItem>
#include <QPainter>

class obstaculo : public QGraphicsItem
{
    int posx;
    int posy;
    int w; //ancho
    int h; //alto

public:
    obstaculo();
    obstaculo(int x,int y, int w, int h);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
};

#endif // OBSTACULO_H
