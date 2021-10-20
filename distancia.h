#ifndef DISTANCIA_H
#define DISTANCIA_H
#include <QGraphicsItem>


class distancia: public QGraphicsTextItem
{
public:
    distancia(QGraphicsItem *parent = nullptr); //Atributos de la clase distancia
    void incrementar(); //Funcion que incrementa las vidas
    int obtenervida(); //Funcion que guarda las vidas
    void reiniciarvidas(); //Funcion que llena las vidas
    void asignarVidas(int puntos);//Funcion que asigna los puntos

private:
    int metros; //Variable donde se guardan  los puntos
};

#endif // DISTANCIA_H
