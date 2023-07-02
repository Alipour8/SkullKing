#ifndef CARD_H
#define CARD_H

#include <QObject>

class Card {
private:
    int value;
    QString type;
    QString owner;
public:
    Card();
    Card(const Card& c1);
    Card(int val, QString ty);
    int get_value();
    void setOwner(QString tmp);
    QString getOwner();
    QString get_type();
};
#endif // CARD_H
