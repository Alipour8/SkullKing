#include "card.h"

Card::Card(){
    Value=0;
    CardName=" ";
    CardNumber=0;
}
Card:: Card(int value,QString card_name,int card_number){
    Value=value;
    CardName=card_name;
    CardNumber=card_number;
}
Card::Card(int card_number,QString card_name){
  CardNumber=card_number;
  CardName=card_name;
}
int Card::getValue(){
    return Value;
}
Card:: Card(const Card& c){
    Value=c.Value;
    CardName=c.CardName;
    CardNumber=c.CardNumber;
}
QString Card:: getCardName(){
    return CardName;
}

int Card::getCardNumber(){
    return CardNumber;
}
void Card:: setOwnerCard(QString owner_card){
   OwnerCard=owner_card;
}
QString Card:: getOwnerCard(){
    return OwnerCard;
}
Card::~Card()
{

}

