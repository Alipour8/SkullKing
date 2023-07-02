#include "history.h"
#include "ui_history.h"
#include"menu.h"

history::history(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::history)
{
    ui->setupUi(this);
}

history::history(user me,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::history)
{
    ui->setupUi(this);
    setWindowTitle("Menu");
    name=me.get_UserName();
    howAmI=me;
}

history::history(QString name,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::history)
{
    ui->setupUi(this);
    setWindowTitle("Menu");
    this->name=name;
}

history::~history()
{
    delete ui;
}

void history::on_show_clicked()
{
        //ui->usernameforforgetpass->hide();
        user his;
        //QString win, pass1, phone, username,lose;
        QString username;
        int win,lose;
        QString Win,Lose;
        //username = ui->usernameforforgetpass->text();

        //phone = ui->phoneforforgetpass->text();
        his.set_UserName(username);
        //forgetpass.set_PhoneNumber(phone);
        //if(database->showhistory(his,win,lose))
        if(database->showhistory(name,win,lose))
        {
            QString Win = QString::number(win);
            QString Lose = QString::number(lose);
            ui->win->setText(Win);
            ui->lose->setText(Lose);
            ui->lineEdit_2->setText("Succesful show");

        }
        else
        {
            ui->lineEdit_2->setText("Sorry, User not found");
        }
        ui->Status->setText("");
}

void history::on_backbtn_clicked()
{
    //hide();
    close();
    menu*log=new menu();
    log->show();
}
