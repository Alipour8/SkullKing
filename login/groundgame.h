#ifndef GROUNDGAME_H
#define GROUNDGAME_H
#include <QObject>
#include <iostream>
#include "card.h"
#include <algorithm>
using namespace std;
class GroundGame
{
public:
    list<Card> Ground;
    pair<QString,int> GroundWinner();
    GroundGame();
};

#endif // GROUNDGAME_H
