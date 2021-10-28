#include "ui_mainwindow.h"
#include <QList>
#include <vector>
#include "mainwindow.h"
#include <QString>
#include <QMessageBox> // para imprimir los mensajes en recuadro
#include <QDebug> // para imprimir mensajes
#include <QtGui>
#include <QImage>
#include <stdlib.h>
#include <QLabel>
#include <QPixmap>
#include <time.h>
//#include <QtWidgets>
//#include <QtGui>

#include <QtWidgets>
#include <QtGui>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string.h>
#include <QGraphicsScene>
#include <QGraphicsItem>


//función primer nivel
void MainWindow::primerNivel()
{

    //nivelActual = 1;
    /*
    multijugador = false;
    bandera = true;
    scene = new QGraphicsScene;
    //ui->label_2->hide();

    ui->graphicsView->setScene(scene);

    //Se agrega el personaje a la escena
    personaje_principal = new bolita(90,50,seleccion_personaje);
    scene->addItem(personaje_principal);
    personaje_principal->setScale(0.4);
*/    

    //Botones que se muestran en el GraphicView cuando se abre el juego

    //ocultar botones

    ui->iniciarButton->hide();
    ui->instruccionesButton->hide();
    ui->MultijugadorButton->hide();
    ui->historiaButton->hide();
    //ui->cargarButton->hide();

    scene->setBackgroundBrush(QImage(":/Backgrounds games/nivel1.png"));
            controladorEventos =  new QTimer();
    controladorEventos->start(100);
    connect(controladorEventos,SIGNAL(timeout()),this,SLOT(moverObjetos()));
    //      el que envia la señal, que señal , la clase  ,  slot que recibe

    personaje_principal = new bolita(400,703,seleccion_personaje); //x,y,tamaño
    scene->addItem(personaje_principal);

    nubePrueba =  new Nube(true);
    scene->addItem(nubePrueba);

    Obstaculos.push_back(new obstaculo(0,0,700,20));
    scene->addItem(Obstaculos.back());

    Obstaculos.push_back(new obstaculo(0,200,700,20));
    scene->addItem(Obstaculos.back());

    Obstaculos.push_back(new obstaculo(0,0,20,400));
    scene->addItem(Obstaculos.back());

    Obstaculos.push_back(new obstaculo(340,0,20,400));
    scene->addItem(Obstaculos.back());


}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    /*controladorEventos =  new QTimer();
    controladorEventos->start(100);
    connect(controladorEventos,SIGNAL(timeout()),this,SLOT(moverObjetos()));
    //      el que envia la señal, que señal , la clase  ,  slot que recibe
    */


    ui->setupUi(this);
   // ui->eliminarPartida->hide();
   // ui->cargarPartida->hide();
    scene= new QGraphicsScene();
    scene= new QGraphicsScene(0, 0, 1920, 1080);
    ui->graphicsView->setScene(scene);
    /*
   // scene->setSceneRect(0,0,700,450);
    personaje_principal = new bolita(220,274,seleccion_personaje); //x,y,tamaño
    scene->addItem(personaje_principal);

    nubePrueba =  new Nube(true);
    scene->addItem(nubePrueba);

    Obstaculos.push_back(new obstaculo(0,0,700,20));
    scene->addItem(Obstaculos.back());

    Obstaculos.push_back(new obstaculo(0,200,700,20));
    scene->addItem(Obstaculos.back());

    Obstaculos.push_back(new obstaculo(0,0,20,400));
    scene->addItem(Obstaculos.back());

    Obstaculos.push_back(new obstaculo(340,0,20,400));
    scene->addItem(Obstaculos.back());*/
}

MainWindow::~MainWindow()
{
    delete ui;
}



bool MainWindow::EuvalarColision(void)
{
    bool colision = false;
    QList<obstaculo*>:: Iterator it; //itarador para recorrer la lista de obstaculos
    for(it= Obstaculos.begin(); it!= Obstaculos.end(); it++){

        /*if((*it)-> collidesWithItem(personaje_principal))
           colision = true;*/
    }
    return colision;
}


void MainWindow::moverObjetos()
{
    if(personaje_principal->getsalto() == true){
        personaje_principal->saltando();

    }
    else{
        controladorEventos->stop();

    }
}

void MainWindow::keyPressEvent(QKeyEvent *evento)
{
    if(evento->key()==Qt::Key_D)
    {
        if(!this->EuvalarColision())
            personaje_principal->MoveRight();
        personaje_principal->actualizar_sprite_derecha();
    }

    else if(evento->key()==Qt::Key_A)
    {
        if(!this->EuvalarColision())
            personaje_principal->MoveLeft();
        personaje_principal->actualizar_sprite_izquierda();
    }

    else if(evento->key()==Qt::Key_W)
    {
        if(!this->EuvalarColision()){
            personaje_principal->setsalto(true);
            controladorEventos->start(20);
        }
        if(personaje_principal->getsalto()== true){

        }

    }
    /* for (int i = 0; i<listadulces.size(); i++) {
            if (personaje_principal->collidesWithItem(listadulces.at(i))){
                scene->removeItem(listadulces.at(i));
                listadulces=modificarFrutaBurbuja(listadulces,i);




                }
        }*/

}

void MainWindow::on_iniciarButton_clicked()
{
    primerNivel();
}


void MainWindow::on_instruccionesButton_clicked()
{




}


void MainWindow::on_MultijugadorButton_clicked()
{

}

void MainWindow::GuardarPartidaButton_3_clicked()
{
    if(guardar==0)
    {
        //Se escribe en el archivo guardar el cual es el fichero con permisos de escritura
        ofstream Fichero;
        Fichero.open("guardar.txt",ios::out| ios::app);//Se abre el archivo
        Fichero<<nombre_usuario.toStdString()<<" "<<to_string(nivelActual)<<" "<<to_string(Puntos->obtenerPuntos())<<endl;
        Fichero.close();//Se cierra el archivo
        guardar=0;
    }
    guardar=0;
}

void MainWindow::CargarPartidaButton_2_clicked()
{
    bool existePartida = false;
    cout<<"1Cargarr";
    if(escogerPersonaje==1 || escogerPersonaje==2){//Condicion para Jugar en CargarPartida
        //Variables de lectura
        string nombrePos;
        string nivelPos;
        string puntosPos;
        ifstream archivo;
        archivo.open("guardar.txt");//Se abre el archivo
        cout<<"2";
        while(!archivo.eof())
        {
            archivo>>nombrePos;
            archivo>>nivelPos;
            archivo>>puntosPos;
            cout<<"3";
            if(nombrePos==nombre_usuario.toStdString())
            {
                nivelActual = stoi(nivelPos)+1;//Se pone al personaje en nivel 2
                Puntos->asignarPuntos(stoi(puntosPos));//Se convierten los puntos en int
                existePartida=true;//Se verifica que exista la partida
                //Se ponen a correr los timers
                ui->bottonMultijugador->hide();
                timercaida = new QTimer();
                connect(timercaida,SIGNAL(timeout()),this,SLOT(activaG()));
                timercaida->start(30);
                timerfrutaburbuja = new QTimer();
                connect(timerfrutaburbuja,SIGNAL(timeout()),this,SLOT(actualizar_frutaburbuja()));
                timerfrutaburbuja->start(150);
                timerportalRickMorty = new QTimer();
                connect(timerportalRickMorty,SIGNAL(timeout()),this,SLOT(actualizar_portal()));
                timerportalRickMorty->start(200);
                //Se carga desde el segundo nivel
                segundoNivel();
            }
        }
        archivo.close();//Se cierra el archivo
        cout<<"4";
        if(existePartida==false){//Condicion en caso tal que el usuario no haya jugado

            Mensaje.setText("DEBES HABER JUGADO EN MODO: 1 JUGADOR");
            Mensaje.setInformativeText("");
            Mensaje.exec();

        }
    } else{
        Mensaje.setText("DEBES ESCOGER UN PERSONAJE PARA JUGAR");
        Mensaje.setInformativeText("");
        Mensaje.exec();

    }

}

void MainWindow::on_historiaButton_clicked()
{

}


