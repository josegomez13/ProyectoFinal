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
#include <obstaculo.h>

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
    Ui::MainWindow *ui;
    bolita *bola;
    QList<obstaculo*>Obstaculos;
    QGraphicsScene *scene;
    void keyPressEvent(QKeyEvent *evento); //reconocer cuando una tecla ha sido presionada
};
#endif // MAINWINDOW_H
