/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QMenuBar *menubar;
    QMenu *menuOpciones;
    QMenu *menuTransformaciones;
    QMenu *menuPosici_n;
    QMenu *menuInformaci_n;
    QMenu *menuAlgoritmos_ML;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1400, 1200);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(220, 50, 161, 50));
        QFont font;
        font.setFamily(QString::fromUtf8("Roboto Condensed"));
        font.setPointSize(24);
        label->setFont(font);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(700, 50, 161, 50));
        label_2->setFont(font);
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(110, 100, 350, 350));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(700, 100, 350, 350));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(470, 100, 141, 28));
        QIcon icon(QIcon::fromTheme(QString::fromUtf8("image-loading")));
        pushButton->setIcon(icon);
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(470, 150, 141, 28));
        QIcon icon1(QIcon::fromTheme(QString::fromUtf8("edit-undo")));
        pushButton_2->setIcon(icon1);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1400, 25));
        menuOpciones = new QMenu(menubar);
        menuOpciones->setObjectName(QString::fromUtf8("menuOpciones"));
        menuTransformaciones = new QMenu(menubar);
        menuTransformaciones->setObjectName(QString::fromUtf8("menuTransformaciones"));
        menuPosici_n = new QMenu(menubar);
        menuPosici_n->setObjectName(QString::fromUtf8("menuPosici_n"));
        menuInformaci_n = new QMenu(menubar);
        menuInformaci_n->setObjectName(QString::fromUtf8("menuInformaci_n"));
        menuAlgoritmos_ML = new QMenu(menubar);
        menuAlgoritmos_ML->setObjectName(QString::fromUtf8("menuAlgoritmos_ML"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuOpciones->menuAction());
        menubar->addAction(menuTransformaciones->menuAction());
        menubar->addAction(menuPosici_n->menuAction());
        menubar->addAction(menuAlgoritmos_ML->menuAction());
        menubar->addAction(menuInformaci_n->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Input Image", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Input Image", nullptr));
        label_3->setText(QString());
        label_4->setText(QString());
        pushButton->setText(QCoreApplication::translate("MainWindow", "Seleccionar", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Restaurar", nullptr));
        menuOpciones->setTitle(QCoreApplication::translate("MainWindow", "Opciones", nullptr));
        menuTransformaciones->setTitle(QCoreApplication::translate("MainWindow", "Transformaciones ", nullptr));
        menuPosici_n->setTitle(QCoreApplication::translate("MainWindow", "Posici\303\263n", nullptr));
        menuInformaci_n->setTitle(QCoreApplication::translate("MainWindow", "Informaci\303\263n", nullptr));
        menuAlgoritmos_ML->setTitle(QCoreApplication::translate("MainWindow", "Algoritmos ML", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
