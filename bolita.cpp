#include "bolita.h"
#include <QPixmap>
#include <QTimer>
#include <math.h>
#include <cmath>



//retorna un booleano que permite afirmar si el personaje esta en el aire.
bool bolita::getsalto() const
{
    return salto;
}

//Actulizacion del booleano segun la condiciones que se usen, este valor varia
void bolita::setsalto(bool value)
{
    salto = value;
}

//retorna el valor de la velocidad a la que va el personaje
int bolita::getvelocidad() const
{
    return velocidad;
}

//Actualizacion de la velocidad del personaje en sus movimientos:derecha ,izquierda y salto.
void bolita::setvelocidad(int value)
{
    velocidad = value;
}

float bolita::getancho() const
{
    return ancho;
}

void bolita::setancho(float value)
{
    ancho = value;
}

float bolita::getalto() const
{
    return alto;
}

void bolita::setalto(float value)
{
    alto = value;
}


bolita::bolita(int x, int y, int ElElla)//Constructor que recibe como atributos la posicion x y y un valor entero que decide que personaje seleccionar
{  //Se usa this para indicar el objeto actual en el que se trabajo, esto para evitar confusiones con las variables locales y dar seguridad que se esta trabajando en esta

    this->posx=x;//Posicion en x del personaje
    this->posy=y;//Posicion en y del personaje

   setPos(posx, posy); // dar la posición

   //opciones para los personajes ---> (1). El  (2). Ella

   if(ElElla == 1){ // Se escoge como personaje al gordito
         this->pixmap = new QPixmap("PONER CARPETA DE LA IMAGEN.PNG");
   }

   else if(ElElla == 2){ // Se escoge como personaje a la gordita
         this->pixmap = new QPixmap("PONER CARPETA DE LA IMAGEN.PNG");
   }

   //Distancia en X y Y  a la que el personaje está en la ventana del juego inicialmente
   this->dx = 4;
   this->dy =4;

   //Ancho y alto de la imagen del personaje
   this->ancho = 124;
   this->alto=160;

   //Gravedad del personaje
   this->gravedad = 1;

   //Booleano que indica si el personaje esta en tierra o no
   this->tierra = true;

   //Booleano que indica si el personaje esta en el aire o no
   this->salto = false;

   //Retorna el valor de la posicion del personaje en el eje x
   int bolita::getposx() const
   {
       return posx;
   }
   //Actualiza el valor de la posicion del personaje en el eje x
   void bolita::setposx(int value)
   {
       posx = value;
   }
   //Retorna el valor de la posicion del personaje en el eje y
   int bolita::getposy() const
   {
       return posy;
   }
   //Actualiza el valor de la posicion del personaje en el eje y
   void bolita::setposy(int value)
   {
       posy = value;
   }


}

QRectF bolita::boundingRect() const // BoundingRect, es donde se va a dibujar el personaje

{
    return QRectF(-ancho/2,-alto/2,ancho,alto);
}

void bolita::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-ancho/2,-alto/2,*pixmap,dy,dx,ancho,alto);

}

void bolita::caidaLibre()
{   //Movimiento de Caida libre
    if(this->posy>450){
        tierra=true;
        this->salto = false;
        tiempo = 0;
    }
    //Se verifica si el personaje esta en el aire o no
    if (tierra==false){
        if (salto == true){
            posy+=(-(this->velocidad)+((gravedad*(this->tiempo))));//Ecuacion caida libre
        } else{
            posy+=((gravedad*(this->tiempo)));//Ecuacion caida libre
        }
        tiempo+= 0.5; }//Incremento del tiempo

        //Se obtiene la posicion del personaje cuando se realizó el movimiento de caida libre
        setPos(posx,posy);
    this->update(-ancho/2,-alto/2,ancho,alto);//Actualizacion de la posicion en todo instante de tiempo

}

void bolita::saltar()
{   //Funcion saltar
    if (this->tiempo == 0){
        this->tiempo = 1;
        posy-= this->velocidad*this->tiempo;//Formula de caida Libre
        this->salto = true;//Se verifica si esta en el aire o no
    }
    //Se obtiene la posicion del personaje cuando se realizo el salto
      setPos(posx,posy);

}

//Movimiento Lineal hacia la izquierda
void bolita::MoveLeft()
{   if(posx>10){    //Se limita el movimiento del personaje en la escena
    posx -= (velocidad/2);
    setPos(posx,posy);}
}
//Movimiento Lineal hacia la derecha
void bolita::MoveRight()
{   if(posx<940){   //Se limita el movimiento del personaje en la escena
    posx += (velocidad/2);
    setPos(posx,posy);}
}

//Funcion que verifica si el personaje esta en tierra a traves del booleano tierra

void bolita::enelsuelo()
{
    tierra = true;
    this->salto = false;
    tiempo = 0;
}

//Se actualiza, recorre el sprite como una matriz tanto para la izquierda como derecha
//Estas cantidades están en Pixeles

void bolita::actualizar_sprite_derecha()
{   //Se recorre la matriz y se varia dy de a 128 pixeles para que el personaje se vea caminando
    //dx es estático dado que solo recorre la tercera fila
    dx=333;
    dy+=128;
    if(dy >=128*4)
    {
        dy=0;
    }
    this->update(-ancho/2,-alto/2,ancho,alto);//Se actualiza la aparicion del personaje en pantalla
}

void bolita::actualizar_sprite_izquierda()
{
    //Se recorre la matriz y se varia dy de a 128 pixeles para que el personaje se vea caminando
    //dx es estatico dado que solo recorre la segunda fila
    dx=168;
    dy+=128;
    if(dy >= 128*4)
    {
        dy=0;
    }
    this->update(-ancho/2,-alto/2,ancho,alto);//Se actualiza la aparicion del personaje en pantalla

}



