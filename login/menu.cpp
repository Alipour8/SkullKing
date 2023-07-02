#include "menu.h"
#include "ui_menu.h"

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
    //log=new class login();
    //log->show();
}

void menu::on_setting_clicked()
{
    set=new class setting(howAmI);
    set->show();
    //hide();
}

void menu::on_history_clicked()
{
    his=new class history(name);
    his->show();
}

void menu::on_start_game_clicked()//server game
{
   // skuul=new class SkullGame();
   // skuul->show();
}

void menu::on_start_game_2_clicked()//client game
{
   // client=new class PlayClient();
   // client->show();
}

