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

#include <QtWidgets>
//#include <QMediaPlayer>
//#include <QSound>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string.h>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <dulces.h>
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
    ui->CargarPartidaButton_2->hide();
    ui->GuardarPartidaButton_3->hide();

    scene->setBackgroundBrush(QImage(":/Backgrounds games/nivel1.png"));
    //ui->graphicsView->resize(1000,1000);
    //this->resize(1000,1000);

    int iteradorGotitas = 0;
    while (iteradorGotitas < 16){
        gotita = new gotitas(600+(900*iteradorGotitas));
        listaGotitas.push_back(gotita);
        scene->addItem(gotita);
        iteradorGotitas += 1;
    }


    controladorEventos =  new QTimer();
    controladorEventos->start(100);
    connect(controladorEventos,SIGNAL(timeout()),this,SLOT(moverObjetos()));
    //      el que envia la señal, que señal , la clase  ,  slot que recibe

    personaje_principal = new bolita(400,750,seleccion_personaje); //x,y,tamaño
    scene->addItem(personaje_principal);

    nubePrueba =  new Nube(true, personaje_principal);
    scene->addItem(nubePrueba);


    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->centerOn(personaje_principal->x(), personaje_principal->y());


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

    scene= new QGraphicsScene(0, 0, 15312, 1041);

    ui->graphicsView->setScene(scene);

}

MainWindow::~MainWindow()
{
    delete ui;
}

QList<gotitas *> MainWindow::modificarGotitas(QList<gotitas *> listaGotitas, int posicion)
{
    listaGotitas.removeAt(posicion);
    return listaGotitas; //Retorna la lista actualizada
}
//Funcion que remueve de la listaVida la vida que el personaje Perdio
QList<Vida *> MainWindow::modificarVida(QList<Vida *> listaVida, int posicion)
{
    listaVida.removeAt(posicion);
    return listaVida;//Retorna la lista actualizada

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

    for(int i=0; i<listaGotitas.count();i++){
        gotitas *gotitaActual = listaGotitas.at(i);
        if(gotitaActual-> collidesWithItem(personaje_principal))
            scene->removeItem(gotitaActual);
            listaGotitas.removeOne(gotitaActual);
            cout << "zoe" <<i<<endl;
    }

    if(personaje_principal->getsalto() == true){
        personaje_principal->saltando();

    }
    else{
        controladorEventos->stop();

    }

}

void MainWindow::actualizar_gotitas()
{
    for(int i=0; i<listaGotitas.count();i++){
        listaGotitas[i]->sprite_gotita();
    }
}

void MainWindow::actualizar_vida()
{
    // si el personaje colisiona con un dulce pierde vida

    for (int i = 0; i<dulces.count(); i++){
        if (personaje_principal->collidesWithItem(dulces.at(i))){
            scene->removeItem(listaVida.at(0));//Se remueve la vida de escena
            listaVida=modificarVida(listaVida,0);
            if(listaVida.count()==0){
                muerte();//Si la lista esta vacia se invoca la funcion muerte
            }
        }
    }
}


//funcion muerte del personaje

void MainWindow::muerte()
{
    QMessageBox mensaje;
    mensaje.setIconPixmap(QPixmap(":/Backgrounds games/gorditocaido.PNG"));
    mensaje.show();
    mensaje.exec();
    QApplication::quit();
}

void MainWindow::pantallaMenu()
{

}

void MainWindow::keyPressEvent(QKeyEvent *evento)
{
    if(evento->key()==Qt::Key_D)
    {
        if(!this->EuvalarColision())
            personaje_principal->MoveRight();
        personaje_principal->actualizar_sprite_derecha();
        ui->graphicsView->centerOn(personaje_principal->x(), personaje_principal->y());

    }

    else if(evento->key()==Qt::Key_A)
    {
        if(!this->EuvalarColision())
            personaje_principal->MoveLeft();
        personaje_principal->actualizar_sprite_izquierda();
        ui->graphicsView->centerOn(personaje_principal->x(), personaje_principal->y());

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

}

void MainWindow::on_iniciarButton_clicked()
{
    ui->label->hide();
    ui->label_2->hide();
    ui->label_3->hide();
    ui->label_4->hide();
    primerNivel();
}


void MainWindow::on_instruccionesButton_clicked()
{
<<<<<<< HEAD
  QTextStream io;
  QFile arch;
  QString contenido;

  arch.setFileName(":/Instrucciones.txt");
  arch.open(QIODevice::Text | QIODevice::ReadOnly);
  io.setDevice(&arch);
   contenido = io.readAll();
   arch.close();
  qDebug() << contenido;
=======

>>>>>>> d61ca65449744a17e88e77e9283bdebc9b591cda

}


void MainWindow::on_MultijugadorButton_clicked()
{

}

void MainWindow::on_historiaButton_clicked()
{

}

void MainWindow::GuardarPartidaButton_3_clicked()
{
    if(guardar==0)
    {
        //Se escribe en el archivo guardar el cual es el fichero con permisos de escritura
        ofstream Fichero;
        Fichero.open("guardar.txt",ios::out| ios::app);//Se abre el archivo
        //Fichero<<nombre_usuario.toStdString()<<" "<<to_string(primerNivel())<<" "<<to_string(metros->obtenervida())<<endl;
        Fichero.close();//Se cierra el archivo
        guardar=0;
    }
    guardar=0;
}

void MainWindow::on_eliminarPartida_clicked()
{

}

void MainWindow::CargarPartidaButton_2_clicked()
{
    bool existePartida = false;
    cout<<"Cargar";
    // if(escogerPersonaje==1 || escogerPersonaje==2){//Condicion para Jugar en CargarPartida
    //Variables de lectura
    string nombrePos;
    string puntosPos;
    ifstream archivo;
    archivo.open("guardar.txt");//Se abre el archivo
    cout<<"2";
    while(!archivo.eof()) //Mientras el archivo este abierto, lleve al archivo las variables
    {
        archivo>>nombrePos;
        archivo>>puntosPos;
        cout<<"3";
        if(nombrePos==nombre_usuario.toStdString())
        {

            metros->asignarVidas(stoi(puntosPos));//Se convierten los puntos en int
            existePartida=true;//Se verifica que exista la partida

        }
    }


    archivo.close();//Se cierra el archivo
    cout<<"4";
    if(existePartida==false){//Condicion en caso tal que el usuario no haya jugado

        /*  Mensaje.setText("DEBES HABER JUGADO EN MODO: 1 JUGADOR");
            Mensaje.setInformativeText("");
            Mensaje.exec();

        }
    else{
        Mensaje.setText("DEBES ESCOGER UN PERSONAJE PARA JUGAR");
        Mensaje.setInformativeText("");
        Mensaje.exec();


    }
*/
    }


}

