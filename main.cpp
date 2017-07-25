#include "mainwindow.h"

//#include <QGuiApplication>
#include <QApplication>
#include <QScreen>
#include <QThread>

int main(int argc, char *argv[])
{
//    QGuiApplication app(argc, argv);
    QApplication app(argc, argv);

    MainWindow window;
    window.show();

    return app.exec();
}
