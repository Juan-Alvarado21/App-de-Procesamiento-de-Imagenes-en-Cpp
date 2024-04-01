#ifndef TRANSFORMACIONES_H
#define TRANSFORMACIONES_H
#include<iostream>
#include<src/ImageInfoWindow/imageinfowindow.h>
#include<QImage>
#include<math.h>


class Transformaciones
{
public:
    Transformaciones();

public slots:
    QPixmap Filtro_BN(QString );
    QPixmap Filtro_Binario(QString, int);
    QPixmap Filtro_BinarioInv(QString, int);
    QPixmap Filtro_Negativo(QString);
    QPixmap Filtro_AjusteBrillo(QString ,int);
    QPixmap Filtro_AjusteContraste(QString , int );
    QPixmap Filtro_Parabola(QString img_path, int escalar);
    QPixmap Filtro_ParabolaInv(QString img_path, int escalar);
    QPixmap Filtro_Posterizado(QString img_path, int escalar);

private:

        pxl** transf_bitmap;

};

#endif // TRANSFORMACIONES_H
