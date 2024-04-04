#include "laboratorio.h"
#include "ui_laboratorio.h"

Laboratorio::Laboratorio(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Laboratorio)
{
    ui->setupUi(this);
}

Laboratorio::~Laboratorio()
{
    delete ui;
}
cdc
