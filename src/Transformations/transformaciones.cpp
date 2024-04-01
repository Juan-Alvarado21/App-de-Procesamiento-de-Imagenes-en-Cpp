#include "src/Transformations/transformaciones.h"
#include<QDebug>
#include<QFileInfo>
#include<src/MainWindow/mainwindow.h>

Transformaciones::Transformaciones(){
}

/*
 * Implementación de la coleccion de filtros
 * Esta clase se encarga de calcular las transformaciones directas del bitmap para un mejor nivel de
 * abstracción.
 *
 */


QPixmap Transformaciones:: Filtro_BN(QString img_path) {
    QImage image(img_path);

    if(image.isNull()){
        qDebug() << "Error: No se pudo cargar la imagen desde el camino proporcionado.";
    }
else{
        ImageInfoWindow imageinfo;
        pxl** map= imageinfo.procesar_bitmap(img_path);
        int media=0;

        /* Promediamos valores entre planos para obtener gris */

      for(int i=0; i<image.height(); i++){
          for(int j=0; j<image.width();j++){
              media= ((map[j][i].r+map[j][i].g+map[j][i].b)/3);
              image.setPixel(j,i,qRgb(media,media,media));
          }
      }

    image.save(img_path);

    // Limpieza de memoria para el mapa de bits
    for(int i = 0; i < image.width(); i++) {
        delete[] map[i]; // Liberar cada array de pxl
    }
    delete[] map; // Liberar el array de punteros

    }

    QPixmap returned_img(img_path);

return returned_img;
}




QPixmap Transformaciones:: Filtro_Negativo(QString img_path) {
    QImage image(img_path);

    if(image.isNull()){
        qDebug() << "Error: No se pudo cargar la imagen desde el camino proporcionado.";
    }
else{
        ImageInfoWindow imageinfo;
        pxl** map= imageinfo.procesar_bitmap(img_path);


      for(int i=0; i<image.height(); i++){
          for(int j=0; j<image.width();j++){
              image.setPixel(j,i,qRgb(255-map[j][i].r,255-map[j][i].g,255-map[j][i].b));
          }
      }


    image.save(img_path);

    // Limpieza de memoria para el mapa de bits
    for(int i = 0; i < image.width(); i++) {
        delete[] map[i]; // Liberar cada array de pxl
    }
    delete[] map; // Liberar el array de punteros

    }

    QPixmap returned_img(img_path);

return returned_img;
}






QPixmap Transformaciones::Filtro_Binario(QString img_path,int umbral) {
    QPixmap pixmap = Filtro_BN(img_path);
    QImage image = pixmap.toImage();

    if(image.isNull()) {
        qDebug() << "Error: No se pudo cargar la imagen desde el camino proporcionado.";
        return QPixmap(); // Return an empty pixmap on failure
    }

    ImageInfoWindow imageinfo;
    pxl** map = imageinfo.procesar_bitmap(img_path); //Llamamos al metodo de mapa de bits al crear la clase imageinfo

    // Asignación dinámica de la memoria para la transformacion en un solo plano

    int** matriz = new int*[image.width()];
    for(int i = 0; i < image.width(); i++) {
        matriz[i] = new int[image.height()];
    }

    // Mapeamos valores binarios en 1 umbral

    for(int i = 0; i < image.height(); i++) {
        for(int j = 0; j < image.width(); j++) {
            if(map[j][i].r > umbral) {
                matriz[j][i] = 255;
            } else {
                matriz[j][i] = 0;
            }
            image.setPixel(j, i, qRgb(matriz[j][i], matriz[j][i], matriz[j][i])); // Apply binary value
        }
    }

    // Liberamos memoria dinámica
    for(int i = 0; i < image.width(); i++) {
        delete[] matriz[i];
    }
    delete[] matriz;

    image.save(img_path);

    return QPixmap::fromImage(image);
}






QPixmap Transformaciones::Filtro_BinarioInv(QString img_path,int umbral) {
    QPixmap pixmap = Filtro_BN(img_path);

    QImage image = pixmap.toImage();

    if(image.isNull()) {
        qDebug() << "Error: No se pudo cargar la imagen desde el camino proporcionado.";
        return QPixmap();
    }

    ImageInfoWindow imageinfo;
    pxl** map = imageinfo.procesar_bitmap(img_path);


    int** matriz = new int*[image.width()];
    for(int i = 0; i < image.width(); i++) {
        matriz[i] = new int[image.height()];
    }


    for(int i = 0; i < image.height(); i++) {
        for(int j = 0; j < image.width(); j++) {
            if(map[j][i].r > umbral) {
                matriz[j][i] = 0;
            } else {
                matriz[j][i] = 255;
            }
            image.setPixel(j, i, qRgb(matriz[j][i], matriz[j][i], matriz[j][i]));
        }
    }

    // Liberamos memoria dinámica
    for(int i = 0; i < image.width(); i++) {
        delete[] matriz[i];
    }
    delete[] matriz;

    image.save(img_path);

    return QPixmap::fromImage(image);
}






QPixmap Transformaciones::Filtro_AjusteBrillo(QString img_path, int escalar) {
    QImage image(img_path);

    if(image.isNull()) {
        qDebug() << "Error: No se pudo cargar la imagen desde el camino proporcionado.";
        return QPixmap();
    }

    for(int y = 0; y < image.height(); y++) {
        for(int x = 0; x < image.width(); x++) {
            QColor colorActual(image.pixel(x, y));

            //Se encarga de hacer que la transformacion quede en el rango de 0-255

            int r = qBound(0, colorActual.red() + escalar, 255);
            int g = qBound(0, colorActual.green() + escalar, 255);
            int b = qBound(0, colorActual.blue() + escalar, 255);
            image.setPixel(x, y, qRgb(r, g, b));

}
    }

    image.save(img_path);

    return QPixmap::fromImage(image);
}





QPixmap Transformaciones::Filtro_AjusteContraste(QString img_path, int escalar) {
    QImage image(img_path);

    if(image.isNull()) {
        qDebug() << "Error: No se pudo cargar la imagen desde el camino proporcionado.";
        return QPixmap();
    }

    for(int y = 0; y < image.height(); y++) {
        for(int x = 0; x < image.width(); x++) {
            QColor colorActual(image.pixel(x, y));

            double factor = (259.0 * (escalar + 255.0)) / (255.0 * (259.0 - escalar));
            int r = qBound(0, int(factor * (colorActual.red() - 128) + 128), 255);
            int g = qBound(0, int(factor * (colorActual.green() - 128) + 128), 255);
            int b = qBound(0, int(factor * (colorActual.blue() - 128) + 128), 255);

            image.setPixel(x, y, qRgb(r, g, b));

}
    }

    image.save(img_path);

    return QPixmap::fromImage(image);
}





QPixmap Transformaciones::Filtro_Parabola(QString img_path, int escalar) {
    QImage image(img_path);

    if(image.isNull()) {
        qDebug() << "Error: No se pudo cargar la imagen desde el camino proporcionado.";
        return QPixmap();
    }

    for(int y = 0; y < image.height(); y++) {
        for(int x = 0; x < image.width(); x++) {
            QColor colorActual(image.pixel(x, y));

            int op_r= 255*pow((colorActual.red()/escalar),2);
            int op_g= 255*pow((colorActual.green()/escalar),2);
            int op_b= 255*pow((colorActual.blue()/escalar),2);
            int r = qBound(0, op_r, 255);
            int g = qBound(0, op_g, 255);
            int b = qBound(0, op_b, 255);

            image.setPixel(x, y, qRgb(r, g, b));
}
    }

    image.save(img_path);

    return QPixmap::fromImage(image);
}





QPixmap Transformaciones::Filtro_ParabolaInv(QString img_path, int escalar) {
    QImage image(img_path);

    if(image.isNull()) {
        qDebug() << "Error: No se pudo cargar la imagen desde el camino proporcionado.";
        return QPixmap();
    }

    for(int y = 0; y < image.height(); y++) {
        for(int x = 0; x < image.width(); x++) {
            QColor colorActual(image.pixel(x, y));

            int op_r= 255-255*pow((colorActual.red()/escalar),2);
            int op_g= 255-255*pow((colorActual.green()/escalar),2);
            int op_b= 255-255*pow((colorActual.blue()/escalar),2);
            int r = qBound(0, op_r, 255);
            int g = qBound(0, op_g, 255);
            int b = qBound(0, op_b, 255);

            image.setPixel(x, y, qRgb(r, g, b));

}
    }

    image.save(img_path);

    return QPixmap::fromImage(image);
}




QPixmap Transformaciones::Filtro_Posterizado(QString img_path, int escalar) {
    QImage image(img_path);

    if(image.isNull()) {
        qDebug() << "Error: No se pudo cargar la imagen desde el camino proporcionado.";
        return QPixmap();
    }

    // Preparación de umbrales
    int umbrales[escalar];
    for(int aux = 0; aux < escalar; aux++) {
        umbrales[aux] = 255 * (aux + 1) / escalar - 1; //Declara un arreglo segun el numero de umbrales
    }

/* Se asegura de mappear los pixeles segun el umbral donde cae */

    auto ajustarColor = [&umbrales, escalar](int color) -> int {
        for(int i = 0; i < escalar; i++) {
            if(color <= umbrales[i]) {
                if (i == 0) return umbrales[0];
                int difA = color - umbrales[i-1];
                int difB = umbrales[i] - color;
                return difA < difB ? umbrales[i-1] : umbrales[i];
            }
        }
        return 255; // Retorna el maximo en caso contrario
    };


    // Manda a llamar al bloque de ajuste
    for(int y = 0; y < image.height(); y++) {
        for(int x = 0; x < image.width(); x++) {
            QColor originalColor = image.pixelColor(x, y);
            int red = ajustarColor(originalColor.red());
            int green = ajustarColor(originalColor.green());
            int blue = ajustarColor(originalColor.blue());
            image.setPixelColor(x, y, QColor(red, green, blue));
        }
    }


     image.save(img_path);

    return QPixmap::fromImage(image);
}










