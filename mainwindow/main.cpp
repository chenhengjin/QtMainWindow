#include "mainwindow.h"
#include <QApplication>
#include <QObject>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.setWindowTitle("My App");
    w.show();

    PaintedWidget p;
    p.show();

    return a.exec();
}
