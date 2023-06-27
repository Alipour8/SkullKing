#include "deck.h"
#include "ui_deck.h"
#include "card.h"
#include <QDebug>
#include<list>
#include <algorithm>
using namespace std;
deck::deck(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::deck)
{
    ui->setupUi(this);
}
deck::deck(){

    Card Queen(5,"Queen");
    for(int i=0;i<3;i++){
    card_list.push_back(Queen);
    }
     Card King(4,"King");
    for(int i=0;i<3;i++){
        card_list.push_back(King);
    }
    Card Pirate(3,"Pirate");
     for(int i=0;i<4;i++){
        card_list.push_back(Pirate);
    }
    for(int i=0;i<8;i++){
    Card Parrot(1,"Parrot",i);
    card_list.push_back(Parrot);
    }
    for(int i=0;i<8;i++){
    Card Map(1,"Map",i);
    card_list.push_back(Map);
    }
    for(int i=0;i<8;i++){
    Card Treasure(1,"Treasure",i);
    card_list.push_back(Treasure);
    }
   for(int i=0;i<8;i++){
       Card PirateFlag(2,"PirateFlag",i);
       card_list.push_back(PirateFlag);
   }
}
deck::~deck()
{
    delete ui;
}

