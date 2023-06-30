#include "rules.h"
#include "ui_rules.h"
#include <QPixmap>
#include <QBitmap>
#include <QWidget>
#include<QPushButton>


rules::rules(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::rules)
{
    ui->setupUi(this);

    //QPixmap image("C:/Users/ASUS/Downloads/rules.jpg");
    //ui->label->setPixmap(image);
    //ui->label->setMask(image.mask());


    setWindowTitle("Rules/Skull king");
    //setFixedSize(717, 1280);

//log=new class login;
//connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(hide()));
}

rules::~rules()
{
    delete ui;
}


void rules::on_pushButton_clicked()
{
   this->hide();
    rules2*url=new rules2();
    url->show();
}
