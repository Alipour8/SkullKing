#ifndef GROUND_H
#define GROUND_H

#include <QObject>
#include <iostream>
#include "card.h"
using namespace std;
class Ground {
public:
    QList<Card> ground;
    Ground();
    QPair<QString, int> GroundWinner();
};
#endif // GROUND_H
