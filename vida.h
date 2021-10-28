#ifndef VIDA_H
#define VIDA_H
#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QGraphicsScene>
#include <QMainWindow>
#include <QObject>
#include <QWidget>

class Vida: public QObject, public QGraphicsItem
{

    int posx,posy;//Posicion en x y y de las vidas
    QPixmap *pixmapVidaAgua;//Pixmap:Imagen de la vida
    private://Variables privadas de la clase vida
    int dx,dy,ancho,alto;//posicion en x y y segun el sistema de coordenadas y ancho y alto de la imagen
    public:
    Vida(int x,int y);//Atributos de la clase vida
    //Posicion en x
    int getPosx() const;//Retorna un entero de la posicion en x
    void setPosx(int value);//Actualiza la posicion en x
    //Posicion en y
    int getPosy() const;//Retorna un entero de la posicion en y
    void setPosy(int value);//Actualiza la posicion en y
    QRectF boundingRect() const;// para dibujar el cuerpo
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
};

#endif // VIDA_H
