#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QList> // para utilizar el Qlist
#include <QDesktopWidget>
#include <QDebug>// para imprimir mensajes en la terminal
#include <QMessageBox> // para imprimir mensajes como recuadros
#include <QVector> // para usar los Qvector
#include <iostream>//Flujo de entrada y salida para leer los archivos
#include <fstream> // para los archivos
#include <QRectF>
#include <iterator>
#include <QMessageBox>
#include <QListWidget>


// MIS CLASES

#include <bolita.h>
#include <nube.h>
#include <obstaculo.h>
#include <distancia.h>
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    bool bandera;
    Ui::MainWindow *ui;
    QString nombre_usuario; // Variable que guardará el nombre del usuario
    int guardar = 0;
    bool multijugador = false;
    int seleccion_personaje, seleccion_personaje2 = 1; //entero que dice cual de los dos personajes se escogió
    int distancia_recorrida; // distancia recorrida por el personaje en el "trote"
    QMessageBox msgBox; //Varible Cuadro de texto
    distancia *metros; //puntero metros de la clase distancia
    bolita *personaje_principal; //puntero para el personaje principal con los atributos de la clase bolita :3

    QList<obstaculo*>Obstaculos;
    QGraphicsScene *scene;
    void keyPressEvent(QKeyEvent *evento); //reconocer cuando una tecla ha sido presionada
    bool EvaluarColision();
};
#endif // MAINWINDOW_H
