#include "login.h"
#include "ui_login.h"

#include <QPixmap>
#include <QBitmap>
#include <QWidget>
#include<QPushButton>
#include"singup.h"
#include"rules.h"
#include"maindatabase.h"
#include<QDebug>

login::login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::login)
{
    ui->setupUi(this);
    //ui->eye->setHidden(true);

       //QPixmap image("C:/Users/ASUS/Downloads/login.jpg");
       //ui->label->setPixmap(image);
       //ui->label->setMask(image.mask());


       setWindowTitle("Skull king");

       //setFixedSize(1402, 2472);

       //singup=new class singup;
       rules=new class rules;
       connect(ui->exit,SIGNAL(clicked()),this,SLOT(close()));
       //connect(ui->rules,SIGNAL(clicked()),this,SLOT(close()));

       //connect(ui->pushButton_3,SIGNAL(clicked()),singup,SLOT(show()));
       connect(ui->rules,SIGNAL(clicked()),rules,SLOT(show()));
       //maindatabase*data=new maindatabase();
       database = new maindatabase();
}

login::~login()
{
    delete ui;
}



void login::on_rule_clicked()
{
  rules->show();

}

void login::on_forgetpassbtn_clicked()
{
    close();
   forgetpassword*forget=new forgetpassword();
   forget->show();
}

void login::on_regButton_clicked()
{
    //close();
    singup*sign=new singup();
    sign->show();
}


void login::on_checkBox_showpass_stateChanged(int arg1)
{
    if(arg1)
           ui->passwordBox->setEchoMode(QLineEdit::Normal);
       else
           ui->passwordBox->setEchoMode(QLineEdit::Password);
}

void login::on_loginButton_clicked()
{
    this->loggedIn = Login(ui->usernameBox->text(), ui->passwordBox->text());

        if(this->loggedIn)
        {
            this->username = ui->usernameBox->text();
            this->password = ui->passwordBox->text();
            //login::hide();

            //we should add menu here
            Menu=new menu(inneruser);
            Menu->show();

        }
        else
        {
            ui->loginLabel->setText("Login failed: Invalid credentials!");
        }
    }

    bool login::Login(QString u, QString p)
    {
        inneruser.set_UserName(u);
        inneruser.set_Password(p);
        if(maindatabase::Find_user(inneruser))
            return true;
        return false;
    }

