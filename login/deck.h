#ifndef DECK_H
#define DECK_H

#include <QObject>
#include <list>
#include "card.h"
class Deck {
public:
    QList<Card> deck;
    Deck();
    void refresh();
};

#endif // DECK_H
