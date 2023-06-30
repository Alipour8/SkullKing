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
    //log=new login();
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
    his=new class history(howAmI);
    his->show();
}

void menu::on_start_game_clicked()
{
    //wait for game and client-server
}
