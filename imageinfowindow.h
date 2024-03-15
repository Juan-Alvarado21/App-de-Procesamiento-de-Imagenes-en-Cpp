#ifndef IMAGEINFOWINDOW_H
#define IMAGEINFOWINDOW_H

#include <QLabel>
#include <QImage>
#include<QString>
#include <QDialog>


namespace Ui{
    class ImageInfoWindow;
}


class ImageInfoWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ImageInfoWindow(QWidget *parent = nullptr);
    ~ImageInfoWindow();

public slots:

    //void showImageInfo(QString img_input);

private:
    Ui:: ImageInfoWindow * ui;
    // QLabel *infoLabel;

};

#endif // IMAGEINFOWINDOW_H
