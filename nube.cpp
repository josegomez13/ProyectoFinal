#include "nube.h"
#include "nube.h"
#include <math.h>
#include <cmath>
#include<QDebug>
#include <bolita.h>




Nube::Nube(bool bandera, bolita *personaje)
{
    this->PX=200;
    this->PY=200;
    this->ancho=600;
    this->alto=400;
    //srand(time(0));
    //timer= new QTimer();
    //timer->start(500);
    //connect(timer,SIGNAL(timeout()),this,SLOT(controladorDeMovimientos()));
    this->dx=0;
    this->dy=600;
    this->personajePrincipal = personaje;


    // CENTRA
    this->setTransformOriginPoint(this->boundingRect().center());

    VY=25; // velo en y
    AX=0;// acel en x
    AY=0; // acel en y
    g=1; //gravedad
    V=0; //vector de velocidad;
    dt=0.02; // delta de tiempo
    this->pixmap=new QPixmap(":/Backgrounds games/nube.png");//direccion del sprite
    setScale(0.5);
    amplitud =  25;
    velocidad = 150;
    //this->moverHaciaDerecha = true;
    // this->ciclosLanzamientoDulces = 0;




    // inicializar el timer //
    srand(time(0));
    timer =  new QTimer();
    timer->start(50);
    connect(timer,SIGNAL(timeout()),this,SLOT(controladorDeMovimientos()));


}


void Nube::actualizarPosyVel()//funcion para realizar el calculo de la posicion y la velocidad
{
    V = pow(((VX*VX)+(VY*VY)),(1/2));//velocidad total
    angulo = atan2(VY,VX);// arcotangente
    AX= -((K*(V*V)*(R*R))/mass)*cos(angulo);//aceleracion en X
    AY= (-((K*(V*V)*(R*R))/mass)*sin(angulo))-g;//aceleración en Y
    PX = PX + ((VX*(dt)))+(((AX*(dt*dt)))/2);//pos en X
    PY = PY + ((VY*(dt)))+(((AY*(dt*dt)))/2);//pos en Y
    VX = VX + AX*dt;//velocidad en X
    VY = VY + AY*dt;//velocidad en Y
}


QRectF Nube::boundingRect() const
{
    // boundingrect, es donde se va a dibujar.
    return QRectF(-ancho/2,-alto/2,ancho,alto);
}




void Nube::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-ancho/2,-alto/2,*pixmap,dy,dx,ancho,alto);

}

void Nube::set_vel(float vx, float vy, float px, float py)
{
    VX=vx;//le asigno la velocidad calculada a Velocidad en x
    VY=vy;//le asigno la velocidad calculada a Velocidad en y
    PX=px;//le asigno la posicion calculada en X
    PY=py;//le asigno la posicion calculada en Y
}



void Nube::actual(float v_limit)
{
    this->actualizarPosyVel();//actualizo la pisicion y la velocidad del objeto
    setPos(this->getPX(),v_limit-this->getPY());//le asigno la posicion en X y Y al objeto
}


float Nube::getPX() const
{
    return PX;
}

float Nube::getPY() const
{
    return PY;
}

float Nube::getMass() const
{
    return mass;
}

float Nube::getR() const
{
    return R;
}

float Nube::getVX() const
{
    return VX;
}

float Nube::getVY() const
{
    return VY;
}


void Nube::moverSinuidalmente()
{
    sumador = sumador + 0.02;
    if (sumador >= 2){
        sumador = 0;
    }
    setPos(PX, PY + amplitud*sin(2*3.1415*sumador/2)); //ecuación del movimiento sinusoidal de la nube

}


void Nube::moverErraticamente()
{
    this->PX=this->PX+ 1+rand()%10;// movimientos que se le puede implementar a la nube
    this->PY = this->PY + 1+rand()%10;

}

void Nube::moverZigZag() // movimientos que se le puede implementar a la nube
{

    if (this->PX< 10 ) {
        // movernos hacia la derecha
        this->moverHaciaDerecha = true;
    }
    if (this->PX > 15000) {
        // movernos hacia la izquierda
        this->moverHaciaDerecha = false;
    }


    if (this->moverHaciaDerecha==true) {
        this->PX=this->PX+12;
    }
    else{
        this->PX = this->PX-12;
    }


}

void Nube::generarDulces()
{
    // vamos a implementar la generacion de dulces que caeran a partir de la posx posy
    // de la nube
    if (this->ciclosLanzamientoDulces>2000) {
        dulceSorpresa =  new Dulces(this->PX,this->PY);

        arregloDulces.push_back(dulceSorpresa);

        std::cout << "NUBE --> x : "<<this->PX<< " y : " << this->PY << std::endl;
        scene()->addItem(arregloDulces.back());
        this->ciclosLanzamientoDulces=0;
        //this->timer->stop();



    }
    else{
        if(this->getPX()<7000){
            // 50 mils
            this->ciclosLanzamientoDulces+=150;
        } else {
            // 125 mils
            this->ciclosLanzamientoDulces+=200;
        }
    }


    // AQUI
    int i = 0;
    for (auto &iterador:arregloDulces) {
        iterador->caerDulceConstantement();
        if (iterador->comprobarColision()==true) {
            scene()->removeItem(iterador);
            arregloDulces.removeAt(i);
            std::cout << "El dulce ha sido eliminado" <<std::endl;

            //arregloDulces.at(i);
        }
        if(iterador->collidesWithItem(this->personajePrincipal)){
            this->personajePrincipal->setVidas(this->personajePrincipal->getVidas()-1);
            scene()->removeItem(iterador);
            arregloDulces.removeAt(i);
            std::cout << "El dulce ha colisionado con el personaje y ha sido eliminado" <<std::endl;
        }
        i++;
    }

}

void Nube::setPY(float newPY)
{
    PY = newPY;
}


void Nube::controladorDeMovimientos()
{
    this->moverSinuidalmente(); // movimiento en x
    this->moverZigZag(); // movimiento en y
    generarDulces();
    // this->setPos(this->PX,this->PY);
    scene()->update();

}

