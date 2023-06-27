#include "card.h"
#include "ui_card.h"

Card::Card(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Card)
{
    ui->setupUi(this);
}
Card:: Card(int value,QString card_name,int card_number){
    Value=value;
    CardName=card_name;
    CardNumber=card_number;
}
Card::Card(int value,QString card_name){
  Value=value;
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
Card::~Card()
{
    delete ui;
}

void Card::on_pushButton_clicked()
{

}

