#include "massagelose.h"
#include "ui_massagelose.h"

massagelose::massagelose(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::massagelose)
{
    ui->setupUi(this);
}

massagelose::~massagelose()
{
    delete ui;
}
