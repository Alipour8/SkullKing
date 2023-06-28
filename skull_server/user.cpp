#include "user.h"
#include "ui_user.h"

user::user(QByteArray text, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::user)
{
    ui->setupUi(this);
    ui->textEdit->setText(text);
}

user::~user()
{
    delete ui;
}
