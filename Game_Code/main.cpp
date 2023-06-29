#include "skullgame.h"
#include "playclient.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SkullGame w;
    PlayClient x;


    w.show();
    x.show();
    return a.exec();
}
