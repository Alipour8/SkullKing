// Created A.R.M.A on ۰۴/۰۶/۲۰۲۳.
#ifndef SKULL_GAME_CARD_H
#define SKULL_GAME_CARD_H
#include <iostream>
#include <string>
#include <list>
using namespace std;
class Card{
private:
    int Value;
    string Name;
public:
    // constructor
    Card(int value,string name);
    Card();
    // copy constructor
    Card(const Card &C1);
    // setter & getter function
    void setValue(int value);
    void setName(string name);
    int getValue();
    string getName();
    list<Card> cards;
};

#endif //SKULL_GAME_CARD_H

