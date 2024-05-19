/********************************************************************************
** Form generated from reading UI file 'imageinfowindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGEINFOWINDOW_H
#define UI_IMAGEINFOWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_ImageInfoWindow
{
public:

    void setupUi(QDialog *ImageInfoWindow)
    {
        if (ImageInfoWindow->objectName().isEmpty())
            ImageInfoWindow->setObjectName(QString::fromUtf8("ImageInfoWindow"));
        ImageInfoWindow->setWindowModality(Qt::WindowModal);
        ImageInfoWindow->resize(800, 600);

        retranslateUi(ImageInfoWindow);

        QMetaObject::connectSlotsByName(ImageInfoWindow);
    } // setupUi

    void retranslateUi(QDialog *ImageInfoWindow)
    {
        ImageInfoWindow->setWindowTitle(QCoreApplication::translate("ImageInfoWindow", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ImageInfoWindow: public Ui_ImageInfoWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGEINFOWINDOW_H
