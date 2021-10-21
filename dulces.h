#ifndef DULCES_H
#define DULCES_H

#include <QObject>
#include <QGraphicsItem>
#include <QObject>
#include <QPainter>
#include <QGraphicsScene>
#include <iostream>
#include <QTimer>
#include <QList>

class Dulces : public QGraphicsItem, public QObject // se realiza herencia
{

private:
    int ancho;
    int alto;
    float posx;
    float posy;
    int   velocidadCaida;

public:
    bool comprobarColision();
    void caerDulceConstantement();
    void actualizar();
    Dulces(float posx, float posy);
    QRectF boundingRect() const; // para dibujar el cuerpo
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

};

#endif // DULCES_H
