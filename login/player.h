#ifndef PLAYER_H
#define PLAYER_H

#include <QWidget>
#include <list>
#include "card.h"
#include <iostream>
#include "deck.h"
namespace Ui {
class Player;
}

class Player : public QWidget
{
    Q_OBJECT

public:
    //constructor
    explicit Player(QWidget *parent = nullptr);
    Player();
    Player(QString name,QString user_name,QString phone_number,QString email,QString password,int coin);
    void Play();
    void shareHand(deck &temp,int round);
    void startGame();
    //copy constructor
    Player(const Player &p);

    ~Player();

private:
    Ui::Player *ui;
    QString Name;
    QString UserName;
    QString PhoneNumber;
    QString Email;
    QString Password;
    int Coin;
    int Score;
    int PlayerNumber;
    list<Card> Hand;
    static int Id;
    deck playerCard;
};

#endif // PLAYER_H
