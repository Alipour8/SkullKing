#include "deck.h"
#include "ui_deck.h"
#include "card.h"
#include <QDebug>
#include<list>
#include <algorithm>
using namespace std;

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
   list<Card> temp;
       for (;!card_list.empty();)
       {
           int x = rand();
           x %= card_list.size();
           std::list<Card>::iterator it = card_list.begin();
           for (int j = 0; j < x; j++)
               it++;
           temp.push_back(*it);
           card_list.erase(it);
       }
       for(list<Card>::iterator it = temp.begin(); it != temp.end(); it++)
           card_list.push_back(*it);
   }
list<Card> deck:: getCardList(){
    return card_list;
}
pair<int,int> deck::compareCard(){
    list<Card> ground;
 Card p1=ground.front();
 ground.pop_front();
 Card p2=ground.front();
 if(p1.getCardName() != "PirateFlag" && p1.getCardName() != "Pirate" &&
         p1.getCardName() != "Queen" && p1.getCardName() != "King"){

     if ((p2.getCardName() == "PirateFlag" || p2.getCardName() == "Pirate" ||
         p2.getCardName() == "Queen" || p2.getCardName() == "King")) {
         int score;
         if (p2.getCardName() == "Queen")
             score = 20;
         else {
             if (p2.getCardName() == "King")
                 score = 15;
             else
                 if (p2.getCardName() == "Pirate")
                     score = 10;
                 else
                     score = 0;
         }
         pair<int, int> tmp(2, score);
         return tmp;
     }
     else {
         if (p2.getCardName() != p1.getCardName()) {
             pair<int, int> tmp(1, 0);
             return tmp;
         }
         else {
             if (p2.getValue() < p1.getValue()) {
                 pair<int, int> tmp(1, 0);
                 return tmp;
             }
             else {
                 pair<int, int> tmp(2, 0);
                 return tmp;
             }
         }
     }
 }
 else {
     if (p2.getCardName() != "PirateFlag" && p2.getCardName() != "Pirate" &&
         p2.getCardName() != "Queen" && p2.getCardName() != "King") {
         int score;
         if (p1.getCardName() == "Queen")
             score = 20;
         else {
             if (p1.getCardName() == "King")
                 score = 15;
             else
                 if (p1.getCardName() == "Pirate")
                     score = 10;
                 else
                     score = 0;
         }
         pair<int, int> tmp(1, score);
         return tmp;
     }
     else {
         if(p1.getCardName() == "PirateFlag" && p2.getCardName() == "PirateFlag")
             if (p1.getValue() > p2.getValue()) {
                 pair<int, int> tmp(1, 0);
                 return tmp;
             }
             else {
                 pair<int, int> tmp(2, 0);
                 return tmp;
             }
         else {
             if (p1.getCardName() == "PirateFlag" ^ p2.getCardName() == "PirateFlag") {
                 if (p1.getCardName() == "PirateFlag") {
                     int score;
                     if (p2.getCardName() == "Queen")
                         score = 20;
                     else {
                         if (p2.getCardName() == "King")
                             score = 15;
                         else
                             if (p2.getCardName() == "Pirate")
                                 score = 10;
                     }
                     pair<int, int> tmp(2, score);
                     return tmp;
                 }
                 else {
                     int score;
                     if (p1.getCardName() == "Queen")
                         score = 20;
                     else {
                         if (p1.getCardName() == "King")
                             score = 15;
                         else
                             if (p1.getCardName() == "Pirate")
                                 score = 10;
                     }
                     pair<int, int> tmp(1, score);
                     return tmp;
                 }
             }
             else {
                 if(p1.getCardName() == "Queen")
                     if (p2.getCardName() == "King") {
                         pair<int, int> tmp(2, 35);
                         return tmp;
                     }
                     else
                          if (p2.getCardName() == "Queen") {
                             pair<int, int> tmp(1, 40);
                             return tmp;
                         }
                         else {
                             pair<int, int> tmp(1, 30);
                             return tmp;
                         }
                 if(p1.getCardName() == "King")
                     if (p2.getCardName() == "King") {
                         pair<int, int> tmp(1, 30);
                         return tmp;
                     }
                     else
                         if (p2.getCardName() == "Queen") {
                             pair<int, int> tmp(1, 35);
                             return tmp;
                         }
                         else {
                             pair<int, int> tmp(2, 25);
                             return tmp;
                         }
                 if(p1.getCardName() == "Pirate")
                     if (p2.getCardName() == "King") {
                         pair<int, int> tmp(1, 25);
                         return tmp;
                     }
                     else
                         if (p2.getCardName() == "Queen") {
                             pair<int, int> tmp(2, 30);
                             return tmp;
                         }
                         else {
                             pair<int, int> tmp(1, 20);
                             return tmp;
                         }
             }
         }
     }
 }



}
deck::~deck()
{
    delete ui;
}

