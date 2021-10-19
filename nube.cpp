#include "nube.h"
#include <math.h>
#include <cmath>



/*
--------------------------------------------------------------------------------------------------
                                CONSTRUCTOR DEFECTO

*/
Nube::Nube()
{
    this->temporal=0;
    this->identity=false;
    this->ancho = 79.6;
    this->alto = 120;
    this->limite = 715;
    this->direction = false;
    pixmapNube = new QPixmap(":/Imagenes/1200px-Clouds_Cute_for_CSS_sprites.svg.png");
    setPos(1400,450);
    temporizadorNube = new QTimer();
    temporizadorNube->start(40);
    connect(temporizadorNube,SIGNAL(timeout()),this,SLOT(moverNube()));


    velocidad = 150;//80 + rand() % 120;
    amplitud =  5 + rand() % 10;
    generarDireccion();
    this->dir = true;

}




/*
--------------------------------------------------------------------------------------------------
                               CONSTRUCTOR SOBRECARGADO

*/

Nube::Nube(short op)
{
    this->temporal=0;
    identity = true;
    this->ancho = 91;
    this->alto = 131;
    this->limite = 1360;
    this->direction = false;
    pixmapNube = new QPixmap(":/Imagenes/1200px-Clouds_Cute_for_CSS_sprites.svg.png");
    setPos(1400,1000);
    temporizadorNube= new QTimer();
    temporizadorNube->start(40);
    connect(temporizadorNube,SIGNAL(timeout()),this,SLOT(moverNubeParabolicas()));

    velocidad = 120 + rand() % 180;
    amplitud =  3 + rand() % 8;
    generarDireccion();
    Q_UNUSED(op);
}






/*
--------------------------------------------------------------------------------------------------
                                DESTRUCTOR DE LA CLASE

*/
Nube::~Nube()
{
    short int num = 1+rand()%4;
    //explosiones disponibles para Nube 7 y 10
    if(identity == false){
        switch (num) {
        case 1:{
            scene()->addItem(new Animaciones(pos().x(),pos().y(),10,direction));
            break;
        }
        case 2:{
            scene()->addItem(new Animaciones(pos().x(),pos().y(),7,direction));
            break;
        }
        default:{
            scene()->addItem(new Animaciones(pos().x(),pos().y(),5,direction));
            break;
        }
        }
    }
    else{
        switch (num) {
        case 1:{
            scene()->addItem(new Animaciones(pos().x(),pos().y(),10,direction));
            break;
        }
        case 2:{
            scene()->addItem(new Animaciones(pos().x(),pos().y(),7,direction));
            break;
        }
        default:{
            scene()->addItem(new Animaciones(pos().x(),pos().y(),6,direction));
            break;
        }
        }}
    scene()->removeItem(this);
}






//-------------------------------------------------------------------------------------------
                                    //GRÁFICOS

QRectF Nube::boundingRect() const
{
    return QRectF(-ancho/2,-alto/2,ancho,alto);
}

void Nube::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-ancho/2,-alto/2,*pixmapNube,columnas,0,ancho,alto);
    Q_UNUSED(option)
    Q_UNUSED(widget)
}
//-------------------------------------------------------------------------------------------










/*
------------------------------------------------------------------------------------------------//
                                   ALEATORIEDAD
Alternar de forma aleatoria la ubicación del las Nube enemigoas

*/
void Nube::generarDireccion()
{
    short int modo = 1+rand() % 2;
    if(modo == 1){
        direction = false;
        setPos(1400,100);
    }
    else{
        direction = true;
        setPos(-100,100);
        setTransform(QTransform(-1, 0, 0, 1, boundingRect().width(), 0));
    }
}










/*
-----------------------------------------------------------------------------------------------//
                                ANIMACIONES DEL SPRITE
Alternar sobre los sprites para dar animación a todos los objetos

*/
void Nube::cambiarAnimacion()
{
    columnas = columnas+ancho;
    if (columnas > limite){
        columnas=0;
    }
    this->update(-ancho/2,-alto/2,ancho,alto);
}









/*
-----------------------------------------------------------------------------------------------//
                                    MOVIMIENTOS
movimiento :

*/
void Nube::moverNube()
{
    float dt = 0.02;
    tmp_sumador = tmp_sumador + dt;
    //qDebug()<< " sumador: " <<tmp_sumador<<endl;
    //qDebug()<< " columnas: " <<columnas << "posicion X: "<<pos().x()<<endl;


    if(direction == false){
        setPos(x()-velocidad*dt, y() + amplitud*sin(2*3.1415*tmp_sumador/2));
        setPos(pos().x()-0.5,pos().y());
        //qDebug()<< " velocidad: " <<velocidad<<endl;
    }
    else{
        setPos(x()+velocidad*dt, y() + amplitud*sin(2*3.1415*tmp_sumador/2));
        setPos(pos().x()+0.5,pos().y());
        //qDebug()<< " VELOCIDAD: " <<velocidad<<endl;
    }

    if(pos().x() < -200 || pos().x() > 1400){
        delete this;
    }
    cambiarAnimacion();
    // ------------------ Segmento para la creación de proyectiles tipo asteroides ------------------------ //
    temporal += 40;
    if(temporal > 3000){
        scene()->addItem(new asteroides(pos().x(),pos().y()));
        temporal = 0;
    }
}







/*
----------------------------------------------------------------------------------------------------------//
                                             MOVIMIENTOS #2
Movimiento parabolico : dotar de movimiento de tipo parabólico en aves

*/
void Nube::moverNubeParabolicas()
{
    float dt = 0.02;
    tmp_sumador = tmp_sumador + dt;

    if(direction == false){
        setPos(pos().x()-velocidad*dt , amplitud*sin(3.1415*tmp_sumador/2)+pos().y());
        setPos(pos().x()-0.5,pos().y());
    }
    else{
        setPos(pos().x()+velocidad*dt , amplitud*sin(3.1415*tmp_sumador/2)+pos().y());
        setPos(pos().x()+0.5,pos().y());
    }

    if(pos().x() < -200 || pos().x() > 1400){
        delete this;
    }
    cambiarAnimacion();
}

/* Nube Vieja
Nube::Nube(bool bandera)
{
    alto=120;
    ancho=110;
    if(bandera==true){
    PX=950;//pos x
    VX=-20;// velo en x
    dy=0;

    }
    if(bandera==false){
    PX=50;//pos x
    VX=20;// velo en x
    dy=100;
    }

    PY=rand()%200;//pos y
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
    dt=0.1; // delta de tiempo
    pixmap=new QPixmap(":/Imagenes/1200px-Clouds_Cute_for_CSS_sprites.svg.png");//direccion del sprite
    setScale(0.5);

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
    painter->drawPixmap(-ancho/2,-alto/2,*pixmap,dy,0,ancho,alto);

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
}

*/
