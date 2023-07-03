#include "massagewin.h"
#include "ui_massagewin.h"

massagewin::massagewin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::massagewin)
{
    ui->setupUi(this);
}

massagewin::~massagewin()
{
    delete ui;
}
