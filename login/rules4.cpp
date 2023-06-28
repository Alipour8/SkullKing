#include "rules4.h"
#include "ui_rules4.h"

rules4::rules4(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::rules4)
{
    ui->setupUi(this);
    setWindowTitle("Rules/Skull king");
}

rules4::~rules4()
{
    delete ui;
}

void rules4::on_pushButton_clicked()
{
    this->hide();
    rules5*url=new rules5();
    url->show();
}
