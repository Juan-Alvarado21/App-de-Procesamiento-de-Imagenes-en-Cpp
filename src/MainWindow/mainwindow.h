#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include<QBitmap>
#include<QImage>
#include<QMessageBox>
#include<QFileDialog>
#include "src/ImageInfoWindow/imageinfowindow.h"
#include "src/Transformations/transformaciones.h"



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    ImageInfoWindow *imageinfowindow;
    QString img_input;
    QString img_output;
    pxl** bitmap;
    int slider_value;
    Transformaciones transformacion;

    /* Enumerador de filtros para controlar slider */

    enum FiltroActual {
        Ninguno,
        BN,
        Negativo,
        Binario,
        Binario_invertido,
        Ajuste_Brillo,
        Ajuste_Contraste,
        Parabola,
        Parabola_Inversa,
        Posterizado

    };

    FiltroActual filtro_actual;



private slots:
    void Abrir_imagen();
    void Restaurar_imagen();
    void on_mostrarInfo_action();
    void on_mostrarBitmap_action();
    void on_FiltroBN_action();
    void on_FiltroBN();
    void on_FiltroBinario_action();
    void manejarCambioSlider(int);
    void on_FiltroBinarioInv_action();
    void on_FiltroNegativo_action();
    void on_FiltroAjusteBrillo_action();
    void on_FiltroAjusteContraste_action();
    void on_FiltroParabola_action();
    void on_FiltroParabolaInv_action();
    void on_FiltroPosterizado_action();



private:
    Ui::MainWindow *ui;




};
#endif // MAINWINDOW_H
