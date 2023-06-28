#ifndef CARD_H
#define CARD_H

#include <QWidget>
#include <QString>
#include <QObject>
using namespace std;
namespace Ui {
class Card;
}

class Card : public QWidget
{
    Q_OBJECT
    int Value;
    QString CardName;
    int CardNumber;
    int OwnerCard;

public:
//constructor
   // explicit Card(QWidget *parent = nullptr);
    Card();
    Card(int value,QString card_name,int card_number);
    Card(int value,QString card_name);
//copy constructor
    Card(const Card& );
    QString getCardName();



//setter & getter function
     int getValue();
     void setOwnerCard(int a);
    ~Card();

private slots:
     void on_pushButton_clicked();

private:
    Ui::Card *ui;
};

#endif // CARD_H
