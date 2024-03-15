#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent),
      background(":/path/to/your/image/background.jpg") // Ajusta esta ruta
{
    setFixedSize(1400, 1400); // Establece el tamaño de la ventana
}

MainWindow::~MainWindow()
{
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, width(), height(), background);
}
