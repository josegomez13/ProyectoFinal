#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QList> // para utilizar el Qlist
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
//#include <QMediaPlayer>



#include <QGraphicsScene>
#include <QGraphicsView>



// MIS CLASES

#include <bolita.h>
#include <nube.h>
#include <obstaculo.h>
#include <distancia.h>
#include <vida.h>
#include <gotitas.h>
#include <dulces.h>
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
    QTimer *controladorVidas;
    bool bandera;
    Nube *nubePrueba;
    Ui::MainWindow *ui;
    QString nombre_usuario; // Variable que guardará el nombre del usuario
    int guardar = 0; //contador
    //Dulces

    QList<gotitas *> modificarGotitas(QList<gotitas *> listaGotitas, int posicion);
    QList<gotitas *> listaGotitas;//Declaracion de la lista frutaBurbuja
    gotitas *gotita;

    QList<Vida *> modificarVida(QList<Vida *> listaVida, int posicion);
    QList<Vida *> listaVida;
    int vidas = 3;

    bool multijugador = false;
    int seleccion_personaje = 1, seleccion_personaje2 = 1; //entero que dice cual de los dos personajes se escogió
    int distancia_recorrida; // distancia recorrida por el personaje en el "trote"
    QMessageBox msgBox; //Varible Cuadro de texto
    distancia *metros; //puntero metros de la clase distancia
    bolita *personaje_principal; //puntero para el personaje principal con los atributos de la clase bolita :3
    QList<obstaculo*>Obstaculos;
    QGraphicsScene *scene = new QGraphicsScene(this);
    QGraphicsView *view = new QGraphicsView(this);
    Vida *vida1,*vida2,*vida3;//Creacion de punteros de la clase vida
    QList<Dulces *> dulces;
    void keyPressEvent(QKeyEvent *evento); //reconocer cuando una tecla ha sido presionada
    bool EvaluarColision();
     void primerNivel();


public slots:
    void moverObjetos();
    void CargarPartidaButton_2_clicked();//Funcion Cargar partida
    void GuardarPartidaButton_3_clicked();//Funcion guardar partida
    void on_eliminarPartida_clicked();//Funcion eliminar partida

    void actualizar_vida();//Se actualiza la cantidad de vidas que hay


    void muerte();
    void ganar();
    void pantallaMenu();



private slots:
    void on_iniciarButton_clicked();
    void on_instruccionesButton_clicked();
    void on_historiaButton_clicked();
    void on_CargarPartidaButton_2_clicked();
    //void on_label_5_windowTitleChanged(const QString &title);
    void on_atrasButton_clicked();
};

#endif // MAINWINDOW_H
