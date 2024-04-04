#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "src/ImageInfoWindow/imageinfowindow.h"
#include "src/Transformations/transformaciones.h"
#include <QDateTime>
#include<QDebug>
#include <QIcon>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->slider->setValue(0);



    /* Estilo Css del slider para el escalar  */
    ui->slider->setStyleSheet(R"(
        QSlider::groove:horizontal {
            border: 1px solid #8A2BE2;
            height: 15px;
            background: #17D244;
            margin: 2px 0;
        }

        QSlider::handle:horizontal {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #BA55D3, stop:1 #8A2BE2); /* Gradiente para el controlador */
            border: 1px solid #5c5c5c;
            width: 10px;
            margin: -2px 0;
            border-radius: 6px;
        }
    )");



/*
    //Conexión de los Widgets con eventos en la GUI
    connect(ui->btn_seleccionar,&QPushButton::clicked, this, &MainWindow:: Abrir_imagen);
    connect(ui->btn_restaurar,&QPushButton::clicked, this, &MainWindow:: Restaurar_imagen);
    connect(ui->mostrarInfo, &QAction::triggered,this,&MainWindow::on_mostrarInfo_action );
    //connect(ui->mostrarOperaciones, &QAction::triggered,this,&MainWindow::on_mostrarInfo_action );

    connect(ui->ver_bitmap, &QAction::triggered,this,&MainWindow::on_mostrarBitmap_action );
    connect(ui->action_BN, &QAction::triggered,this,&MainWindow::on_FiltroBN_action);
    connect(ui->action_Binario, &QAction::triggered,this,&MainWindow::on_FiltroBinario_action);
    connect(ui->action_BinarioInv, &QAction::triggered,this,&MainWindow::on_FiltroBinarioInv_action);
    connect(ui->slider,&QSlider::valueChanged,this,&MainWindow::manejarCambioSlider);
    connect(ui->action_Negativo, &QAction::triggered,this,&MainWindow::on_FiltroNegativo_action);
    connect(ui->action_Intensidad, &QAction::triggered,this,&MainWindow::on_FiltroAjusteBrillo_action);
    connect(ui->action_Contraste, &QAction::triggered,this,&MainWindow::on_FiltroAjusteContraste_action);
    connect(ui->action_Parabola, &QAction::triggered,this,&MainWindow::on_FiltroParabola_action);
    connect(ui->action_ParabolaInv, &QAction::triggered,this,&MainWindow::on_FiltroParabolaInv_action);
    connect(ui->action_Posterizado, &QAction::triggered,this,&MainWindow::on_FiltroPosterizado_action);
*/

    connect(ui->slider, &QSlider::valueChanged, this, [=](int value){
        ui->labelValue->setText(QString::number(value));
    });

}


MainWindow::~MainWindow()
{
    delete ui;
}



/* Funcion para Abrir una imagen de múltiples formatos y generar el archivo para la imagen de salida  */

void MainWindow::Abrir_imagen() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Abrir imagen"), QDir::homePath(), tr("Image Files (*.png *.jpg *.bmp *.jpeg *.webp)"));
    if (fileName.isEmpty()) return;

    QPixmap image(fileName);
    if (!image.isNull()) {
        ui->img_input->setPixmap(image.scaled(ui->img_input->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        img_input=fileName;
        if (img_output.isEmpty()) {
            QFileInfo fileInfo(fileName);
            QString fileExtension = fileInfo.suffix();
            QString outputFileName = QCoreApplication::applicationDirPath() + "/salida_" + QDateTime::currentDateTime().toString("yyyyMMddhhmmss") + "." + fileExtension;
            if (image.save(outputFileName, fileExtension.toUpper().toLocal8Bit().constData())) {
                qDebug() << "La imagen ha sido guardada exitosamente en:" << outputFileName;
                img_output = outputFileName;
            } else {
                QMessageBox::critical(this, tr("Error al guardar imagen"), tr("No se pudo guardar la imagen en el archivo de salida."));
            }
        }

        ui->img_output->setPixmap(image.scaled(ui->img_output->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        image.save(img_output);
    } else {
        QMessageBox::critical(this, tr("Error al abrir imagen"), tr("No se pudo cargar la imagen seleccionada."));
    }
}




/* Vuelve a settear en la salida la imagen original  */

void MainWindow::Restaurar_imagen() {
    QImage img_original(img_input);
        QPixmap image = QPixmap::fromImage(img_original);
        if (!image.isNull()) {
            ui->img_output->setPixmap(image.scaled(ui->img_input->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
            image.save(img_output);
        } else {
            QMessageBox::critical(this, "Error", "No se pudo cargar la imagen original para restauración.");
        }
    }






/* Acción para mostrar la información y las estadísticas de la imagen */

void MainWindow:: on_mostrarInfo_action(){

    ImageInfoWindow imageinfowindow;
    imageinfowindow.setModal(true);
    imageinfowindow.setImageInfo(img_output); // llama al metodo para mostrar info en el label
    imageinfowindow.exec();

}

/*Muestra el bitmap de la imagen en un archivo de salida (Proximamente) */

void MainWindow:: on_mostrarBitmap_action(){
    bitmap= imageinfowindow->procesar_bitmap(img_output);
}


/*
void MainWindow::on_mostrar_Operaciones() {

    Operacion *operacion = new Operaciones(this); // Asegúrate de que se destruya con su padre o gestiona su ciclo de vida adecuadamente
    operacion->setWindowModality(Qt::ApplicationModal); // Hace que la ventana sea modal a nivel de aplicación
    operacion->setAttribute(Qt::WA_DeleteOnClose); // Asegura que el objeto se elimine cuando se cierre la ventana
    operacion->show();
}
*/



 /*
  * Aquí empiezan las acciones para controlar las señales con la ui para los filtros
  *
  */




void MainWindow:: on_FiltroBN_action(){


    QPixmap image_proc= transformacion.Filtro_BN(img_output);
    ui->img_output->setPixmap(QPixmap()); // Limpia el pixmap actual
    if(image_proc.isNull()){
        QMessageBox::critical(this, "Error", "No se pudo aplicar el filtro a la imagen.");
    } else{
        ui->img_output->setPixmap(image_proc.scaled(ui->img_output->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        image_proc.save(img_output);
        filtro_actual=BN;
    }
}


void MainWindow:: on_FiltroNegativo_action(){


    QPixmap image_proc= transformacion.Filtro_Negativo(img_output);
    ui->img_output->setPixmap(QPixmap()); // Limpia el pixmap actual
    if(image_proc.isNull()){
        QMessageBox::critical(this, "Error", "No se pudo aplicar el filtro a la imagen.");
    } else{
        ui->img_output->setPixmap(image_proc.scaled(ui->img_output->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        image_proc.save(img_output);
        filtro_actual=Negativo;
    }
}






void MainWindow:: on_FiltroBinario_action(){

    QPixmap image_proc= transformacion.Filtro_Binario(img_output,slider_value);
    ui->img_output->setPixmap(QPixmap()); // Limpia el pixmap actual
    if(image_proc.isNull()){
        QMessageBox::critical(this, "Error", "No se pudo aplicar el filtro a la imagen.");
    } else{
        ui->img_output->setPixmap(image_proc.scaled(ui->img_output->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        image_proc.save(img_output);
        filtro_actual= Binario;
    }
}


void MainWindow:: on_FiltroBinarioInv_action(){

    QPixmap image_proc= transformacion.Filtro_BinarioInv(img_output,slider_value);
    ui->img_output->setPixmap(QPixmap()); // Limpia el pixmap actual
    if(image_proc.isNull()){
        QMessageBox::critical(this, "Error", "No se pudo aplicar el filtro a la imagen.");
    } else{
        ui->img_output->setPixmap(image_proc.scaled(ui->img_output->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        image_proc.save(img_output);
        filtro_actual= Binario_invertido;
    }
}



void MainWindow:: on_FiltroAjusteBrillo_action(){

    QPixmap image_proc= transformacion.Filtro_AjusteBrillo(img_output,slider_value);
    ui->img_output->setPixmap(QPixmap()); // Limpia el pixmap actual
    if(image_proc.isNull()){
        QMessageBox::critical(this, "Error", "No se pudo aplicar el filtro a la imagen.");
    } else{
        ui->img_output->setPixmap(image_proc.scaled(ui->img_output->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        image_proc.save(img_output);
        filtro_actual= Ajuste_Brillo;
    }
}




void MainWindow:: on_FiltroAjusteContraste_action(){

    QPixmap image_proc= transformacion.Filtro_AjusteContraste(img_output,slider_value);
    ui->img_output->setPixmap(QPixmap()); // Limpia el pixmap actual
    if(image_proc.isNull()){
        QMessageBox::critical(this, "Error", "No se pudo aplicar el filtro a la imagen.");
    } else{
        ui->img_output->setPixmap(image_proc.scaled(ui->img_output->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        image_proc.save(img_output);
        filtro_actual= Ajuste_Contraste;
    }
}




void MainWindow:: on_FiltroParabola_action(){
    if(slider_value>0){
    QPixmap image_proc= transformacion.Filtro_Parabola(img_output,slider_value);

    ui->img_output->setPixmap(QPixmap()); // Limpia el pixmap actual
    if(image_proc.isNull()){
        QMessageBox::critical(this, "Error", "No se pudo aplicar el filtro a la imagen.");
    } else{
        ui->img_output->setPixmap(image_proc.scaled(ui->img_output->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        image_proc.save(img_output);
        filtro_actual= Parabola;
    }
    }
}


void MainWindow:: on_FiltroParabolaInv_action(){
     if(slider_value>0){
    QPixmap image_proc= transformacion.Filtro_ParabolaInv(img_output,slider_value);
    ui->img_output->setPixmap(QPixmap()); // Limpia el pixmap actual
    if(image_proc.isNull()){
        QMessageBox::critical(this, "Error", "No se pudo aplicar el filtro a la imagen.");
    } else{
        ui->img_output->setPixmap(image_proc.scaled(ui->img_output->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        image_proc.save(img_output);
        filtro_actual= Parabola_Inversa;
    }
     }
}


void MainWindow:: on_FiltroPosterizado_action(){
     if(slider_value>=0){
    QPixmap image_proc= transformacion.Filtro_Posterizado(img_output,slider_value);
    ui->img_output->setPixmap(QPixmap()); // Limpia el pixmap actual
    if(image_proc.isNull()){
        QMessageBox::critical(this, "Error", "No se pudo aplicar el filtro a la imagen.");
    } else{
        ui->img_output->setPixmap(image_proc.scaled(ui->img_output->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        image_proc.save(img_output);
        filtro_actual= Posterizado;
    }
     }
}




/*
 * Accion por casos segun el filtro seleccionado para el slider
 *
*/



void  MainWindow::manejarCambioSlider(int valor)
{
    slider_value= valor;
    Restaurar_imagen();


    switch (filtro_actual){

    case Binario:
        on_FiltroBinario_action();
        break;

    case Binario_invertido:
        on_FiltroBinarioInv_action();
        break;
    case Ajuste_Brillo:
        on_FiltroAjusteBrillo_action();
        break;

    case Ajuste_Contraste:
        on_FiltroAjusteContraste_action();
        break;

    case Parabola:
        on_FiltroParabola_action();
        break;

    case Parabola_Inversa:
        on_FiltroParabolaInv_action();
        break;

    case Posterizado:
        on_FiltroPosterizado_action();
        break;



   default:
        QMessageBox::critical(this, "Error", "No has aplicado ningun filtro que dependa de rangos.");
        break;
    }

}













