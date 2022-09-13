#include "mainwindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Интерполятор");
    w.resize(1100, 700);
    w.show();
    return a.exec();
}
