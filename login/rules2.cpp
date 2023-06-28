#include "rules2.h"
#include "ui_rules2.h"

rules2::rules2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::rules2)
{
    ui->setupUi(this);
    setWindowTitle("Rules/Skull king");
}

rules2::~rules2()
{
    delete ui;
}

void rules2::on_pushButton_clicked()
{
    this->hide();
    rules3*ru=new rules3();
    ru->show();
}
