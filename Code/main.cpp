#include "mainwindow.h"
#include <QApplication>
#include <ctime>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    srand(time(NULL));
    w.setWindowTitle("RSA Algorithm");
    w.show();
    return a.exec();


}
