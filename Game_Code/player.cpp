#include "player.h"
#include "ui_player.h"
#include "deck.h"
Player::Player(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Player)
{
    ui->setupUi(this);
}

Player::~Player()
{
    delete ui;
}
Player:: Player(QString name,QString user_name,QString phone_number,QString email,QString password,int coin){
    Name=name;
    UserName=user_name;
    PhoneNumber=phone_number;
    Email=email;
    Password=password;
    Coin=coin;
    Id++;
    PlayerNumber=Id;
    Score=0;

}
int Player:: Id=0;
Player::Player(const Player &p) {
    this->Name = p.Name;
    this->UserName = p.UserName;
    this->PhoneNumber = p.PhoneNumber;
    this->Email = p.Email;
    this->Password = p.Password;
    this->Coin = p.Coin;
    this->Score = p.Score;
}
void Player::shareHand(deck &temp,int round){
    list<Card> tempCard;
tempCard=temp.getCardList();
list<Card>::iterator it;
for(int i=0;i<2*round;i++){
it=tempCard.begin();
tempCard.front().setOwnerCard(PlayerNumber);
Hand.push_back(tempCard.front());
tempCard.erase(it);
}

}
void Player::Play(){
    deck d1;
    d1.getCardList();
    list<Card> temp;


}
