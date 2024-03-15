#include "imageinfowindow.h"

ImageInfoWindow::ImageInfoWindow(QWidget *parent)
    : QDialog{parent}{
    setWindowTitle("Información de la Imagen");


}


/*
void ImageInfoWindow::showImageInfo(QString img_input) {

    QImage image(img_input);
    QString info;
    info += "Formato: " + QString::number(image.format()) + "\n";
    info += "Tamaño: " + QString::number(image.width()) + "x" + QString::number(image.height()) + "\n";
    info += "Profundidad de bits: " + QString::number(image.depth()) + "\n";
    info += "Número de colores: " + QString::number(image.colorCount()) + "\n";

    infoLabel->setText(info);
}

*/
