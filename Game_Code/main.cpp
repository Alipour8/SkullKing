#include "skullgame.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SkullGame w;


    w.show();
    return a.exec();
}
