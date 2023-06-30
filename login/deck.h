#ifndef DECK_H
#define DECK_H

#include <QWidget>
#include "card.h"
namespace Ui {
class deck;
}

class deck : public QWidget
{
    Q_OBJECT

public:
   // explicit deck(QWidget *parent = nullptr);
    list<Card>card_list;
    deck();
    list<Card> getCardList();
    pair<int,int> compareCard();

    ~deck();

private:
    Ui::deck *ui;
};

#endif // DECK_H
