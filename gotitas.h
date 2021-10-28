#ifndef GOTITAS_H
#define GOTITAS_H
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

class gotitas: public QObject, public QGraphicsItem

{
public:
    explicit gotitas(QObject *parent = nullptr);//Atributos que pose cada frutaburbuja
    int posx, posy;//Posicion en x y y del personaje
    float dx, dy;  //variables para controlar las filas y las columnas del sprite
    float ancho,alto;//Ancho y alto de la imagen
    QPixmap *pixmap; //pixmap:Imagen de la gotita
    QTimer *timergotitas;//Timer Gotitas
    QRectF boundingRect() const;// para dibujar el cuerpo
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

    //Posicion en x

    int getPosx() const;//Retorna un entero de la posicion en x
    void setPosx(int value);//Actualiza el valor de la posicion en x

    //Posicion en y

    int getPosy() const;//Retorna un entero de la posicion en y
    void setPosy(int value);//Actualiza el valor de la posicion en y

public slots:
    void sprite_gotita();//Funcion que actualiza la gotita

};

#endif // GOTITAS_H