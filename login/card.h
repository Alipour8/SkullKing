#ifndef CARD_H
#define CARD_H

#include <QWidget>
#include <QString>


class Card
{int Value;
    QString CardName;
    int CardNumber;
    int OwnerCard;

public:
//constructor
   // explicit Card(QWidget *parent = nullptr);
    Card(int value,QString card_name,int card_number);
    Card(int value,QString card_name);
//copy constructor
    Card(const Card& );
    QString getCardName();



//setter & getter function
     int getValue();
     int getCardNumber();
     void setOwnerCard(int a);
    ~Card();

public:
    Card();
};

#endif // CARD_H
