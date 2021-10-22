#include "distancia.h"
#include <QFont>

distancia::distancia(QGraphicsItem * padre): QGraphicsTextItem(padre)

{
  //Se crea el puntaje en pantalla como un texto
    metros=0;
    setPlainText(QString("Distancia: ")+ QString::number(metros));//distancia en pantalla como texto y conversion del los numeros en string
    setDefaultTextColor(Qt::white);//Color de puntaje que aparecen en la escena
    setFont(QFont("times new roman",18));//Tipo de letra que tiene puntaje en escena

}

void distancia::incrementar()
{
    metros+=100;//Puntaje incrementa 100 puntos a medida que colisiona con frutaburbujas y mata gusanos
    //setPlainText(QString("Puntaje: ")+ QString::number(puntos));
    setPlainText(QString("Puntaje: ")+ QString::number(1));
}
//Funcion que obtiene los puntos que lleva el personaje
    int distancia::obtenervida()
{
    return metros;
}
//Funcion que sirve para cambiar el sistema de puntaje a 0
    void distancia::reiniciarvidas()
{
    metros=0;

}
//Se guardan los puntos
    void distancia::asignarVidas(int metros)
{
    this->metros = metros;

}
