#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QList> // para utilizar el Qlist
//#include <QDesktopWidget>
#include <QDebug>// para imprimir mensajes en la terminal
#include <QMessageBox> // para imprimir mensajes como recuadros
#include <QVector> // para usar los Qvector
#include <iostream>//Flujo de entrada y salida para leer los archivos
#include <fstream> // para los archivos
#include <QRectF>
#include <iterator>
#include <QMessageBox>
#include <QListWidget>
#include <nube.h>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <bolita.h>
#include <gotitas.h>
#include <dulces.h>
// MIS CLASES

#include <bolita.h>
#include <nube.h>
#include <obstaculo.h>
#include <distancia.h>
#include <vida.h>
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
    //
    // métodos propios

    bool EuvalarColision(void);

    //
    QTimer *controladorEventos;
    bool bandera;
    Nube *nubePrueba;
    Ui::MainWindow *ui;
    QString nombre_usuario; // Variable que guardará el nombre del usuario
    //Dulces
    QList<gotitas *> modificarGotitas(QList<gotitas *> listaGotitas, int posicion);
    QList<gotitas *> listaGotitas;//Declaracion de la lista frutaBurbuja

    QList<Vida *> modificarVida(QList<Vida *> listaVida, int posicion);
    QList<Vida *> listaVida;

    int guardar = 0;
    bool multijugador = false;
    int seleccion_personaje = 1, seleccion_personaje2 = 1; //entero que dice cual de los dos personajes se escogió
    int distancia_recorrida; // distancia recorrida por el personaje en el "trote"
    QMessageBox msgBox; //Varible Cuadro de texto
    distancia *metros; //puntero metros de la clase distancia
    bolita *personaje_principal; //puntero para el personaje principal con los atributos de la clase bolita :3
    QList<obstaculo*>Obstaculos;
    QGraphicsScene *scene = new QGraphicsScene(this);
    QGraphicsView *view = new QGraphicsView(this);
    gotitas *gota1,*gota2,*gota3,*gota4,*gota5,*gota6,*gota7,*gota8,*gota9,*gota10,*gota11,*gota12,*gota13,*gota14,*gota15,*gota16;
    Vida *vida1,*vida2,*vida3,*vida4,*vida5;//Creacion de punteros de la clase vida
    QList<Dulces *> dulces;
    void keyPressEvent(QKeyEvent *evento); //reconocer cuando una tecla ha sido presionada
    bool EvaluarColision();

    //NIVELES

    int nivelActual = 0;
    void primerNivel();
    void segundoNivel();
    void muerte();
    void pantallaMenu();

public slots:
    void moverObjetos();
    void actualizar_gotitas();//Se actualiza la cantidad de gotitas que hay
    void actualizar_vida();//Se actualiza la cantidad de vidas que hay

private slots:
    void on_iniciarButton_clicked();
    void on_instruccionesButton_clicked();
    void on_MultijugadorButton_clicked();
    void on_historiaButton_clicked();
};

#endif // MAINWINDOW_H
