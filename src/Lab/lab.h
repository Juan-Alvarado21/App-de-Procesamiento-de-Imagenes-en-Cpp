#ifndef LAB_H
#define LAB_H

#include <QMainWindow>
#include<QString>
#include<QMessageBox>
#include<QPixmap>
#include<src/ImageInfoWindow/imageinfowindow.h>
#include<src/Transformations/transformaciones.h>
#include<vector>

namespace Ui {
class Lab;
}

class Lab : public QMainWindow
{
    Q_OBJECT

public:
    explicit Lab(QWidget *parent = nullptr);
    ~Lab();
    void mostrar_menu(QString );
    QPixmap filtro_sobel_X(QString);
    void on_sobelX_action();


private:
    Ui::Lab *ui;
    QString img_output;
    QString img_input;
    QString img_op;
};

#endif // LAB_H
