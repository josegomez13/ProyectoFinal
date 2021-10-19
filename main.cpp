#include "mainwindow.h"

#include <QApplication>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>

#include <QKeyEvent>
#include <QDebug>

#include <QTime>
#include <QIcon>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
