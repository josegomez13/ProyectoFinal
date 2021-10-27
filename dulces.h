#ifndef DULCES_H
#define DULCES_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>
#include <QTimer>
#include <QList>
#include <QPixmap>
#include <QGraphicsPixmapItem>




class Dulces : public QGraphicsItem, public QObject // se realiza herencia
{

private:
    int ancho;
    int alto;
    float posx;
    float posy;
    int   velocidadCaida;
    float dx, dy;

public:
    bool comprobarColision();
    void caerDulceConstantement();
    void actualizar();
    Dulces(float posx, float posy);
    QRectF boundingRect() const; // para dibujar el cuerpo
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
    QPixmap *pixmap;//pixmap para el sprite de los dulces

};

#endif // DULCES_H
