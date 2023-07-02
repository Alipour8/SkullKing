#include "deck.h"
#include <iostream>
Deck::Deck() {
    QString types[4] = { "parrot","treasure","map","flag" };
    int vals[8] = { 1,2,3,4,5,6,7,8 };
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            Card tmp(vals[i], types[j]);
            deck.push_back(tmp);
        }
    }
    srand(time(NULL));
    Card c1(0, "skull");
    Card c2(0, "queen");
    Card c3(0, "jack");
    deck.push_back(c1); deck.push_back(c1); deck.push_back(c1);
    deck.push_back(c2); deck.push_back(c2); deck.push_back(c2);
    deck.push_back(c3); deck.push_back(c3); deck.push_back(c3); deck.push_back(c3);
    QList<Card> tmp;
    for (;!deck.empty();)
    {
        int x = rand();
        x %= deck.size();
        QList<Card>::iterator it = deck.begin();
        for (int j = 0; j < x; j++)
            it++;
        tmp.push_back(*it);
        deck.erase(it);
    }
    deck = tmp;
}
void Deck::refresh(){
    Deck tmp;
    this->deck = tmp.deck;
}
