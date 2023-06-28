#include "login.h"

#include <QApplication>
#include<QCoreApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    login w;
    w.show();
    //singup s;
    //s.show();
    return a.exec();
}
