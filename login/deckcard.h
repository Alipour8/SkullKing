#ifndef DECKCARD_H
#define DECKCARD_H
#include "card.h"
#include <QList>
using namespace std;
class DeckCard
{
public:
    QList<Card>card_list;
    list<Card> getCardList();
    pair<int,int> compareCard();
    DeckCard();
};

#endif // DECKCARD_H
