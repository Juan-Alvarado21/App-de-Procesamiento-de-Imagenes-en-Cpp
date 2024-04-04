#include "lab.h"
#include "ui_lab.h"

Lab::Lab(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Lab)
{
    ui->setupUi(this);
}

Lab::~Lab()
{
    delete ui;
}
