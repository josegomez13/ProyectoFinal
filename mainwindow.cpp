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

    //Botones que se muestran en el GraphicView cuando se abre el juego

    //ocultar botones

    ui->label->hide();
    ui->label_2->hide();
    ui->label_3->hide();
    ui->label_4->hide();
    ui->atrasButton->hide();
    ui->iniciarButton->hide();
    ui->instruccionesButton->hide();
    ui->historiaButton->hide();
    ui->CargarPartidaButton_2->hide();
    ui->GuardarPartidaButton_3->hide();

    scene->setBackgroundBrush(QImage(":/Backgrounds games/nivel1.png"));


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

    controladorVidas =  new QTimer();
    controladorVidas->start(100);
    connect(controladorVidas,SIGNAL(timeout()),this,SLOT(actualizar_vida()));

    nombre_usuario = ui->lineEdit->text();
    ui->lineEdit->hide();

    personaje_principal = new bolita(400,750,seleccion_personaje); //x,y,tamaño
    scene->addItem(personaje_principal);
    personaje_principal->setVidas(vidas);

    nubePrueba =  new Nube(true, personaje_principal);
    scene->addItem(nubePrueba);

    int iteradorVidas = 0;
    while (iteradorVidas < 3){ // posicion inicial de las vidas en pantalla
        vida1 = new Vida(personaje_principal->x()+(50*(iteradorVidas-1)), 50);
        listaVida.push_back(vida1);
        scene->addItem(vida1);
        iteradorVidas += 1;
    }

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
    ui->label_5->hide();
    ui->atrasButton->hide();


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

    }
    return colision;
}


void MainWindow::moverObjetos()
{
    //cout << personaje_principal->getVidas()<<"je"<<endl;

    for(int i=0; i<listaGotitas.count();i++){
        if(listaGotitas.at(i)-> collidesWithItem(personaje_principal)){
            if(personaje_principal->getVidas()<3){
                scene->removeItem(listaGotitas.at(i));
                listaGotitas.removeOne(listaGotitas.at(i));

                personaje_principal->setVidas(personaje_principal->getVidas()+1);
            }
        }
    }

    if(personaje_principal->getsalto() == true){
        personaje_principal->saltando();

    }
    else{
        controladorEventos->stop();

    }

}

void MainWindow::actualizar_vida()
{
    // si el personaje colisiona con un dulce pierde vida
    vidas = personaje_principal->getVidas();
    for (int i=0; i<vidas; i++) {
        listaVida.at(i)->show();
    }
    for (int i=vidas; i<3; i++) {
        listaVida.at(i)->hide();
    }
    if(vidas == 0){
        muerte();
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

void MainWindow::ganar()
{
    QMessageBox mensaje;
    mensaje.setIconPixmap(QPixmap(":/Backgrounds games/ganaste.png"));
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
        bool gana = personaje_principal->MoveRight();
        if (gana == true){
            ganar();
        }
        personaje_principal->actualizar_sprite_derecha();
        ui->graphicsView->centerOn(personaje_principal->x(), personaje_principal->y());
        for (int i=0; i<listaVida.count(); i++) {
            listaVida.at(i)->setPosx(personaje_principal->getposx() + 50*(i-1));
            listaVida.at(i)->setPos(listaVida.at(i)->getPosx(), listaVida.at(i)->getPosy());
        }
    }

    else if(evento->key()==Qt::Key_A)
    {
        personaje_principal->MoveLeft();
        personaje_principal->actualizar_sprite_izquierda();
        ui->graphicsView->centerOn(personaje_principal->x(), personaje_principal->y());
        for (int i=0; i<listaVida.count(); i++) {
            listaVida.at(i)->setPosx(personaje_principal->getposx() + 50*(i-1));
            listaVida.at(i)->setPos(listaVida.at(i)->getPosx(), listaVida.at(i)->getPosy());
        }
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
    else if(evento->key()==Qt::Key_G)
    {
        GuardarPartidaButton_3_clicked();
    }

}

void MainWindow::on_iniciarButton_clicked()
{
    primerNivel();
}


void MainWindow::on_instruccionesButton_clicked()
{

}


void MainWindow::on_historiaButton_clicked()
{
    ui->label_5->show();
    ui->atrasButton->show();


}

void MainWindow::GuardarPartidaButton_3_clicked()
{
    if(guardar==0)
    {
        cout << "Guardar"<<endl;
        //Se escribe en el archivo guardar el cual es el fichero con permisos de escritura
        ofstream Fichero;
        Fichero.open("guardar.txt",ios::out| ios::app);//Se abre el archivo
        //Fichero<<nombre_usuario.toStdString()<<" primer nivel "<<to_string(metros->obtenervida())<<endl;
        cout <<nombre_usuario.toStdString()<<" "<<to_string(personaje_principal->getVidas())<<endl;
        Fichero<<nombre_usuario.toStdString()<<" "<<to_string(personaje_principal->getVidas())<<endl;
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
            vidas = stoi(puntosPos);
            //metros->asignarVidas(stoi(puntosPos));//Se convierten los puntos en int
            existePartida=true;//Se verifica que exista la partida
            primerNivel();
        }
    }


    archivo.close();//Se cierra el archivo
    cout<<"4";
    if(existePartida==false){//Condicion en caso tal que el usuario no haya jugado

    }


}


void MainWindow::on_CargarPartidaButton_2_clicked()
{
    bool existePartida = false;
    cout<<"Cargar";
    // if(escogerPersonaje==1 || escogerPersonaje==2){//Condicion para Jugar en CargarPartida
    //Variables de lectura
    string nombrePos;
    string puntosPos;
    ifstream archivo;
    nombre_usuario = ui->lineEdit->text();
    archivo.open("guardar.txt");//Se abre el archivo
    cout<<"2";
    while(!archivo.eof()) //Mientras el archivo este abierto, lleve al archivo las variables
    {
        archivo>>nombrePos;
        archivo>>puntosPos;
        cout<<"3";
        if(nombrePos==nombre_usuario.toStdString())
        {
            vidas = stoi(puntosPos);
            //metros->asignarVidas(stoi(puntosPos));//Se convierten los puntos en int
            existePartida=true;//Se verifica que exista la partida
            primerNivel();
        }
    }


    archivo.close();//Se cierra el archivo
    cout<<"4";
    if(existePartida==false){//Condicion en caso tal que el usuario no haya jugado


    }
}


void MainWindow::on_atrasButton_clicked()
{
    ui->label_5->hide();
    ui->atrasButton->hide();
}

