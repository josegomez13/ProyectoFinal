#include "nube.h"
#include "nube.h"
#include <math.h>
#include <cmath>
#include<QDebug>




Nube::Nube(bool bandera)
{
    this->PX=100;
    this->PY=100;
    this->ancho=20;
    this->alto=20;
    srand(time(0));
    timer= new QTimer();
    timer->start(500);
    connect(timer,SIGNAL(timeout()),this,SLOT(controladorDeMovimientos()));



    // CENTRA
    this->setTransformOriginPoint(this->boundingRect().center());

    // alto=20;
    //ancho=200;
    /*if(bandera==true){
    PX=100;//pos x
    PY=200;
    VX=-20;// velo en x
    dy=0;

    }


    if(bandera==false){
    PX=50;//pos x
    VX=20;// velo en x
    dy=100;
    }
*/


    // PY=rand()%200;//pos y
    mass=5;//masa
    R=10; //radio
    VY=25; // velo en y
    angulo;//angulo
    AX=0;// acel en x
    AY=0; // acel en y
    g=1; //gravedad
    K=(rand()%10)/1000; // resistencia del aire
    //e=(0.5+(rand()%5)/10); // coeficiente de restitucion
    V=0; //vector de velocidad;
    dt=0.02; // delta de tiempo
    pixmap=new QPixmap(":/Imagenes/1200px-Clouds_Cute_for_CSS_sprites.svg.png");//direccion del sprite
    setScale(0.5);
    amplitud =  20;
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
    //return QRectF(ancho/2,alto/2,ancho,alto);
}




void Nube::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //painter->drawPixmap(-ancho/2,-alto/2,*pixmap,dy,0,ancho,alto);
    painter->drawRect(this->PX,this->PY,this->ancho,this->alto);

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

Nube *Nube::nube()
{
    return nube();
    //Nube *nube = new Nube(0);
    //return nube;
}


void Nube::moverSinuidalmente()
{
    sumador = sumador + 0.02;
    qDebug()<< " sumador: " <<sumador<<endl;
    //PY = PY + amplitud*sin(2*3.1415*sumador/2);
    setPos(PX, PY + amplitud*sin(2*3.1415*sumador/2));
    //setPY(PY + amplitud*sin(2*3.1415*sumador/2));
    qDebug()<< " velocidad: " <<velocidad<<endl;


}


void Nube::moverErraticamente()
{
    this->PX=this->PX+ 1+rand()%10;
    this->PY = this->PY + 1+rand()%10;

}

void Nube::moverZigZag()
{

    if (this->PX< 10 ) {
        // movernos hacia la derecha
        this->moverHaciaDerecha = true;
    }
    if (this->PX > 400) {
        // movernos hacia la izquierda
        this->moverHaciaDerecha = false;
    }


    if (this->moverHaciaDerecha==true) {
        this->PX=this->PX+3;
    }
    else{
        this->PX = this->PX-3;
    }


}


void Nube::generarDulces()
{
    // vamos a implementar la generacion de dulces que caeran a partir de la posx posy
    // de la nube
    if (this->ciclosLanzamientoDulces>3000) {
        dulceSorpresa =  new Dulces(this->PX,this->PY);

        arregloDulces.push_back(dulceSorpresa);

        std::cout << "NUBE --> x : "<<this->PX<< " y : " << this->PY << std::endl;
        scene()->addItem(arregloDulces.back());
        this->ciclosLanzamientoDulces=0;
        //this->timer->stop();
    }
    else{
        // 50 mils
        this->ciclosLanzamientoDulces+=50;
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
        i++;
    }

}

void Nube::setPY(float newPY)
{
    PY = newPY;
}


void Nube::controladorDeMovimientos()
{
    this->moverSinuidalmente();
    this->moverZigZag();
    generarDulces();
    // this->setPos(this->PX,this->PY);
    scene()->update();

}

