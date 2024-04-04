#include "lab.h"
#include "ui_lab.h"

Lab::Lab(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Lab)
{
    ui->setupUi(this);

    connect(ui->actionSobelX, &QAction::triggered,this,&Lab::on_sobelX_action);
}

Lab::~Lab()
{
    delete ui;
}


void Lab:: mostrar_menu(QString img_path){
    QPixmap image(img_path);
    if (!image.isNull()) {
        ui->img1->setPixmap(image.scaled(ui->img1->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->img2->setPixmap(image.scaled(ui->img2->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));


     image.save(img_path);
     img_output= img_path;
    } else {
        QMessageBox::critical(this, "Error", "No se pudo cargar la imagen.");
    }
}




#include <vector>

QPixmap Lab::filtro_sobel_X(QString img_path){
    Transformaciones transformacion;
    QPixmap pixmap = transformacion.Filtro_BN(img_path);
    QImage image = pixmap.toImage();

    if(image.isNull()) {
        qDebug() << "Error: No se pudo cargar la imagen desde el camino proporcionado.";
        return QPixmap();
    }

    ImageInfoWindow imageinfo;
    pxl** map = imageinfo.procesar_bitmap(img_path);

    int sobelX[3][3] = { {-1, 0, 1},
                         {-2, 0, 2},
                         {-1, 0, 1} };

    // Convertir la matriz dinámica a un vector de vectores
    std::vector<std::vector<int>> matrizDeEnteros(image.height()+2, std::vector<int>(image.width()+2, 0)); // +2 para el borde
    std::vector<std::vector<int>> aux(image.height(), std::vector<int>(image.width()));

    // Copiar los valores en la matriz ampliada, dejando un marco de ceros para simplificar la convolución
    for(int i = 0; i < image.height(); i++) {
        for(int j = 0; j < image.width(); j++) {
            matrizDeEnteros[i+1][j+1] = map[i][j].r; // Asumiendo map[i][j].r es el valor de intensidad
        }
    }

    // Aplicar el filtro Sobel
    for(int y = 1; y <= image.height(); y++) {
        for(int x = 1; x <= image.width(); x++) {
            int sum = 0;
            for(int i = -1; i <= 1; i++) {
                for(int j = -1; j <= 1; j++) {
                    sum += matrizDeEnteros[y+i][x+j] * sobelX[i+1][j+1];
                }
            }
            // Para asegurarnos que esté en el rango válido [0,255]
            aux[y-1][x-1] = std::min(std::max(sum, 0), 255);
        }
    }

    // Crear una imagen nueva para el resultado
    QImage resultImage(image.width(), image.height(), QImage::Format_RGB32);
    for(int y = 0; y < image.height(); y++) {
        for(int x = 0; x < image.width(); x++) {
            int val = aux[y][x];
            resultImage.setPixelColor(x, y, QColor(val, val, val));
        }
    }


    resultImage.save(img_path);

    return QPixmap::fromImage(resultImage);
}





void Lab:: on_sobelX_action(){

    QPixmap image(img_output);
    img_op= "/home/juan/computer_vision/Analizador/Analizador_imagen/docs/img/sobel.png";
    QPixmap operation(img_op);

    if (!image.isNull()) {
        image= filtro_sobel_X(img_output);
        ui->current->setPixmap(operation.scaled(ui->current->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->img2->setPixmap(image.scaled(ui->img2->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        image.save(img_output);
    } else {
        QMessageBox::critical(this, "Error", "No se pudo cargar la imagen.");
    }
}






