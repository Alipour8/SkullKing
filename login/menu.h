#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include"setting.h"
#include"history.h"
#include"skullgame.h"
#include"playclient.h"

namespace Ui {
class menu;
}

class menu : public QWidget
{
    Q_OBJECT

public:
    menu(user me,QWidget *parent = nullptr);
    explicit menu(QWidget *parent = nullptr);
    ~menu();

private slots:
    void on_logout_clicked();

    void on_setting_clicked();

    void on_history_clicked();

    void on_start_game_clicked();

    void on_start_game_2_clicked();

private:
    Ui::menu *ui;
    setting*set;
    history*his;
    SkullGame*skuul;
    PlayClient*client;
    user howAmI;
    QString name;
    QString mass;
};

#endif // MENU_H
