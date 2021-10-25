#ifndef BOLITA_H
#define BOLITA_H
#include <QGraphicsItem>
#include <QPainter>
#include <QPixmap>
#include <QObject>
#include <QTimer>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QDebug>

class bolita:public QObject, public QGraphicsItem // se realiza herencia
{
    // ATRIBUTOS PARA EL PERSONAJE

private:

    int posx;          // variable de la posición en X del personaje
    int posy;          // variable de la posición en Y del personaje
    int velocidad = 10;     // variable de la velocidad del personaje
    int gravedad;      // variable de la gravedad
    float dx, dy;      // variables que controlan las filas y columnas del sprite
    float ancho, alto; // medidas del personaje
    float tiempo;
    bool tierra;       // booleano que indica si el personaje está parado en la tierra
    bool salto;        // booleano que indica si el personaje está saltando

    QPixmap *pixmap;   // imagen del personaje

public:

    bolita(int x, int y, int ElElla);  // asignación de los atributos al personaje
    QRectF boundingRect() const; // para dibujar el cuerpo
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
    int getposx() const;       //retorna un entero en la posición en x
    void setposx(int newPosx); //actualiza ese valor
    int getposy() const;       //retorna un entero en la posición en y
    void setposy(int newPosy); //actualiza ese valor
    void MoveLeft(); // movimientos lineales del personaje
    void MoveRight();
    void enelsuelo(); //choque del personaje con el suelo



    //boleano que indica si está el personaje en tierra
    bool gettierra() const; //retorna su valor
    void settierra(bool value); //actualiza su valor

    //valor entero para el tiempo
    float gettiempo() const;
    void settiempo(float tiempo);

    //booleano que indica si el personaje está en el aire
    bool getsalto() const;
    void setsalto(bool value);

    //valor entero para la velocidad
    int getvelocidad() const;
    void setvelocidad(int value);

    // ancho del pixmap
    float getancho() const;
    void setancho(float value);

    // alto del pixmap
    float getalto() const;
    void setalto(float value);

    void saltando();//Funcion para el salto de los personajes

    //signals:
public slots:
    void caidaLibre();//Funcion para la caida libre de los personajes
    void actualizar_sprite_derecha();   //Funcion para actualizar el sprite para la derecha
    void actualizar_sprite_izquierda(); //Funcion para actualizar el sprite para la izquierda

private slots:

};

#endif // BOLITA_H
