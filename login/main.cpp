#include "login.h"
#include "skullgame.h"
#include <QApplication>
#include<QCoreApplication>
#include "playclient.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    login w;
    SkullGame x;
    PlayClient y;
    w.show();
    //x.show();
    //y.show();
    //singup s;
    //s.show();
    return a.exec();
}
