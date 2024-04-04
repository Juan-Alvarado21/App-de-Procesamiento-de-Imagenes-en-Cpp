#ifndef IMAGEINFOWINDOW_H
#define IMAGEINFOWINDOW_H

#include <QDialog>
#include<QMessageBox>
#include <QFileInfo>
#include <QFile>
#include<iostream>
#include<vector>
#include<QVector>
#include<QImage>
#include<QColor>
#include <QDebug>
#include"libs/qcustomplot.h"
#include<QIcon>

//Estructura pixel para los canales RGB

typedef struct {
    int r;
    int g;
    int b;
}pxl;


namespace Ui {
class ImageInfoWindow;
}

class ImageInfoWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ImageInfoWindow(QWidget *parent = nullptr);
    ~ImageInfoWindow();
    pxl** local_bitmap;
    int width;
    int height;


 public slots:
    void setImageInfo(QString );
    pxl** procesar_bitmap(QString );
    void GenerarHistograma(QString );
    void GenerarColorScatterPlot(QString);



private:
    Ui::ImageInfoWindow *ui;
    QCPGraph *graphTotal;
    QCPGraph *graphRed;
    QCPGraph *graphGreen;
    QCPGraph *graphBlue;

};

#endif // IMAGEINFOWINDOW_H


