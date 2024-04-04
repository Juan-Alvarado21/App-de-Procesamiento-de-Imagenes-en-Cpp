QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    laboratorio.cpp \
    libs/qcustomplot.cpp \
    src/ImageInfoWindow/imageinfowindow.cpp \
    src/Lab/lab.cpp \
    src/MainWindow/mainwindow.cpp \
    src/Transformations/transformaciones.cpp \
    src/main.cpp \

HEADERS += \
    laboratorio.h \
    libs/qcustomplot.h \
    src/ImageInfoWindow/imageinfowindow.h \
    src/Lab/lab.h \
    src/MainWindow/mainwindow.h \
    src/Transformations/transformaciones.h \

FORMS += \
    laboratorio.ui \
    src/ImageInfoWindow/imageinfowindow.ui \
    src/Lab/lab.ui \
    src/MainWindow/mainwindow.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target



DISTFILES += \
    Analizador_imagen.pro.user
