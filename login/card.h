#ifndef CARD_H
#define CARD_H

#include <QWidget>
#include <QString>


class Card
{int Value;
    QString CardName;
    int CardNumber;
    QString OwnerCard;

public:
//constructor
   // explicit Card(QWidget *parent = nullptr);
    Card(int value,QString card_name,int card_number);
    Card(int card_number,QString card_name);

//copy constructor
    Card(const Card& );




//setter & getter function
    void setOwnerCard(QString owner_card);
    QString getOwnerCard();
     int getValue();
     int getCardNumber();
    QString getCardName();
     void setOwnerCard(int a);
    ~Card();

public:
    Card();
};

#endif // CARD_H
