#include "groundgame.h"

GroundGame::GroundGame(){}

pair<QString,int> GroundGame::GroundWinner(){

 Card p1=Ground.front();
 Ground.pop_front();
 Card p2=Ground.front();
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
         pair<QString, int> tmp(p2.getOwnerCard(), score);
         return tmp;
     }
     else {
         if (p2.getCardName() != p1.getCardName()) {
             pair<QString, int> tmp(p1.getOwnerCard(), 0);
             return tmp;
         }
         else {
             if (p2.getCardNumber() < p1.getCardNumber()) {
                 pair<QString, int> tmp(p1.getOwnerCard(), 0);
                 return tmp;
             }
             else {
                 pair<QString, int> tmp(p2.getOwnerCard(), 0);
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
         pair<QString, int> tmp(p1.getOwnerCard(), score);
         return tmp;
     }
     else {
         if(p1.getCardName() == "PirateFlag" && p2.getCardName() == "PirateFlag")
             if (p1.getCardNumber() > p2.getCardNumber()) {
                 pair<QString, int> tmp(p1.getOwnerCard(), 0);
                 return tmp;
             }
             else {
                 pair<QString, int> tmp(p2.getOwnerCard(), 0);
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
                     pair<QString, int> tmp(p2.getOwnerCard(), score);
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
                     pair<QString, int> tmp(p1.getOwnerCard(), score);
                     return tmp;
                 }
             }
             else {
                 if(p1.getCardName() == "Queen")
                     if (p2.getCardName() == "King") {
                         pair<QString, int> tmp(p2.getOwnerCard(), 35);
                         return tmp;
                     }
                     else
                          if (p2.getCardName() == "Queen") {
                             pair<QString, int> tmp(p1.getOwnerCard(), 40);
                             return tmp;
                         }
                         else {
                             pair<QString, int> tmp(p1.getOwnerCard(), 30);
                             return tmp;
                         }
                 if(p1.getCardName() == "King")
                     if (p2.getCardName() == "King") {
                         pair<QString, int> tmp(p1.getOwnerCard(), 30);
                         return tmp;
                     }
                     else
                         if (p2.getCardName() == "Queen") {
                             pair<QString, int> tmp(p1.getOwnerCard(), 35);
                             return tmp;
                         }
                         else {
                             pair<QString, int> tmp(p2.getOwnerCard(), 25);
                             return tmp;
                         }
                 if(p1.getCardName() == "Pirate")
                     if (p2.getCardName() == "King") {
                         pair<QString, int> tmp(p1.getOwnerCard(), 25);
                         return tmp;
                     }
                     else
                         if (p2.getCardName() == "Queen") {
                             pair<QString, int> tmp(p2.getOwnerCard(), 30);
                             return tmp;
                         }
                         else {
                             pair<QString, int> tmp(p1.getOwnerCard(), 20);
                             return tmp;
                         }
             }
         }
     }
 }



}
