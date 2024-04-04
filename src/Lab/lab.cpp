#include "lab.h"
#include "ui_lab.h"
#include <vector>
#include <QDebug>

Lab::Lab(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Lab)
{
    ui->setupUi(this);
    this->setWindowTitle("Laboratorio de otras Operaciones");
    connect(ui->actionSobelX, &QAction::triggered,this,&Lab::on_sobelX_action);
    connect(ui->actionSobelY, &QAction::triggered,this,&Lab::on_sobelY_action);
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



QPixmap Lab::filtro_sobel_X(QString imgPath) {
    QImage image(imgPath);
    if (image.isNull()) {
        qDebug() << "Error: No se pudo cargar la imagen desde el camino proporcionado.";
        return QPixmap();
    }

    // Convertir la imagen a escala de grises primero
    QImage grayScaleImage = image.convertToFormat(QImage::Format_Grayscale8);

    const int sobelX[3][3] = {{-1, 0, 1},
                              {-2, 0, 2},
                              {-1, 0, 1}};

    QImage resultImage(image.size(), QImage::Format_Grayscale8);

    for (int y = 1; y < grayScaleImage.height() - 1; y++) {
        for (int x = 1; x < grayScaleImage.width() - 1; x++) {
            int sum = 0;
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    int pixelValue = qGray(grayScaleImage.pixel(x + j, y + i));
                    sum += pixelValue * sobelX[i + 1][j + 1];
                }
            }
            // Clamping el resultado entre 0 y 255
            int clampedValue = std::clamp(sum, 0, 255);
            resultImage.setPixelColor(x, y, QColor(clampedValue, clampedValue, clampedValue));
        }
    }

    return QPixmap::fromImage(resultImage);
}



QPixmap Lab::filtro_sobel_Y(QString imgPath) {
    QImage image(imgPath);
    if (image.isNull()) {
        qDebug() << "Error: No se pudo cargar la imagen desde el camino proporcionado.";
        return QPixmap();
    }

    // Convertir la imagen a escala de grises primero
    QImage grayScaleImage = image.convertToFormat(QImage::Format_Grayscale8);

    const int sobelX[3][3] = {{-1, -2, -1},
                              {0, 0, 0},
                              {1, 2, 1}};

    QImage resultImage(image.size(), QImage::Format_Grayscale8);

    for (int y = 1; y < grayScaleImage.height() - 1; y++) {
        for (int x = 1; x < grayScaleImage.width() - 1; x++) {
            int sum = 0;
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    int pixelValue = qGray(grayScaleImage.pixel(x + j, y + i));
                    sum += pixelValue * sobelX[i + 1][j + 1];
                }
            }
            // Clamping el resultado entre 0 y 255
            int clampedValue = std::clamp(sum, 0, 255);
            resultImage.setPixelColor(x, y, QColor(clampedValue, clampedValue, clampedValue));
        }
    }

    return QPixmap::fromImage(resultImage);
}


void Lab::on_sobelX_action() {
    QPixmap image(img_output);
    if (!image.isNull()) {
        // Aplica el filtro Sobel
        QPixmap processedImage = filtro_sobel_X(img_output);
        QPixmap op("/home/juan/computer_vision/Analizador/Analizador_imagen/docs/img/sobel.png");
        // Establece el resultado procesado en ui->img2
        ui->img2->setPixmap(processedImage.scaled(ui->img2->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->current->setPixmap(op.scaled(ui->current->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    } else {
        QMessageBox::critical(this, "Error", "No se pudo cargar la imagen.");
    }
}





void Lab::on_sobelY_action() {


    QPixmap image(img_output);
    QPixmap op("/home/juan/computer_vision/Analizador/Analizador_imagen/docs/img/sobel.png");
    if (!image.isNull()) {
        // Aplica el filtro Sobel
        QPixmap processedImage = filtro_sobel_Y(img_output);
        // Establece el resultado procesado en ui->img2
        ui->img2->setPixmap(processedImage.scaled(ui->img2->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->current->setPixmap(op.scaled(ui->current->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    } else {
        QMessageBox::critical(this, "Error", "No se pudo cargar la imagen.");
    }
}









