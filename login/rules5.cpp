#include "rules5.h"
#include "ui_rules5.h"

rules5::rules5(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::rules5)
{
    ui->setupUi(this);
    setWindowTitle("Rules/Skull king");
}

rules5::~rules5()
{
    delete ui;
}

void rules5::on_pushButton_clicked()
{
    close();
    login*log=new login();
   log->show();
}
