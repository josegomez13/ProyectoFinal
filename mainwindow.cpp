#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene= new QGraphicsScene();
    ui->graphicsView->setScene(scene);
    scene->setSceneRect(0,0,700,450);
    bola= new bolita(10,20,30); //x,y,tamaño
    scene->addItem(bola);

    Obstaculos.push_back(new obstaculo(0,0,700,20));
    scene->addItem(Obstaculos.back());

    Obstaculos.push_back(new obstaculo(0,200,700,20));
    scene->addItem(Obstaculos.back());

    Obstaculos.push_back(new obstaculo(0,0,20,400));
    scene->addItem(Obstaculos.back());

    Obstaculos.push_back(new obstaculo(340,0,20,400));
    scene->addItem(Obstaculos.back());
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::EvaluarColision()
{
    bool colision = false;
    QList<obstaculo*>:: Iterator it; //itarador para recorrer la lista de obstaculos
    for(it= Obstaculos.begin(); it!= Obstaculos.end(); it++){

       if((*it)-> collidesWithItem(bola))
           colision = true;
    }
    return colision;
}

void MainWindow::keyPressEvent(QKeyEvent *evento)
{
    if(evento->key()==Qt::Key_D)
        {
        if(!EvaluarColision())
            bola->MoveRight();
        }

    else if(evento->key()==Qt::Key_A)
    {
        if(!EvaluarColision())
            bola->MoveLeft();
    }



}


