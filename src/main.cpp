#include "src/MainWindow/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //Setteamos el logo
    w.setWindowIcon(QIcon("/home/juan/computer_vision/Analizador/Analizador_imagen/docs/img/racoonized_logo.png"));
    w.show();
    return a.exec();
}
