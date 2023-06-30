#include "rules3.h"
#include "ui_rules3.h"

rules3::rules3(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::rules3)
{
    ui->setupUi(this);
    setWindowTitle("Rules/Skull king");
}

rules3::~rules3()
{
    delete ui;
}

void rules3::on_pushButton_clicked()
{
    this->hide();
    rules4*url=new rules4();
    url->show();
}
