#include "card.h"
using namespace std;
Card::Card() {
    this->value = 0;
    this->type = "";
}
Card::Card(const Card& c1) {
    this->value = c1.value;
    this->type = c1.type;
    this->owner = c1.owner;
}
Card::Card(int val, QString ty) {
    this->value = val; this->type = ty;
}
QString Card::get_type() { return type; }
int Card::get_value() { return value; }

void Card::setOwner(QString tmp) { owner = tmp; }
QString Card::getOwner() { return owner; }
