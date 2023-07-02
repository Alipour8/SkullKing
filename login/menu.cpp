#include "menu.h"
#include "ui_menu.h"
#include"login.h"
#include"setting.h"
#include"history.h"
#include"skullgame.h"
#include"playclient.h"

menu::menu(user me,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::menu)
{
    ui->setupUi(this);
    setWindowTitle("Menu");
    howAmI=me;
    mass="Welcome "+howAmI.get_UserName();
    name=howAmI.get_UserName();
     ui->userusernameforsettinglbl->setText(mass);
}

menu::menu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::menu)
{
    ui->setupUi(this);
    setWindowTitle("Menu");
}

menu::~menu()
{
    delete ui;
}

void menu::on_logout_clicked()
{
    close();
    login*log=new login();
    log->show();
}

void menu::on_setting_clicked()
{
    close();
    setting*log=new setting(howAmI);
    log->show();
    //set=new class setting(howAmI);
    //set->show();
    //hide();
}

void menu::on_history_clicked()
{
    close();
    history*log=new history(name);
    //history*log=new history(howAmI);
    log->show();
    //his=new class history(name);
    //his->show();
}

void menu::on_start_game_clicked()//server game
{
    close();
   SkullGame*skull=new SkullGame(howAmI);
   skull->show();
}

void menu::on_start_game_2_clicked()//client game
{
    close();
   PlayClient*client=new PlayClient(howAmI);
   client->show();
}

