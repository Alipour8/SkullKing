#include "skullgame.h"
#include "deck.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SkullGame w;
    deck d1();

    w.show();
    return a.exec();
}
