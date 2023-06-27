#include "Card.h"
Card::Card(int value, string name) {
    this->Value=value;
    this->Name=name;
}
Card::Card(const Card &C1) {
    this->Value=C1.Value;
    this->Name=C1.Name;
}
Card::Card() {
    string card_name[4]{"Treasure","Map","Parrot","Pirate_Flag"};
    int number[8] = { 1,2,3,4,5,6,7,8 };
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            Card temp(number[i],card_name[j]);
            cards.push_back(temp);
        }
    }
    srand(time(NULL));
    Card c1(0, "Skull");
    Card c2(0, "Queen");
    Card c3(0, "King");
    cards.push_back(c1);
    cards.push_back(c1);
    cards.push_back(c1);
    cards.push_back(c2);
    cards.push_back(c2);
    cards.push_back(c2);
    cards.push_back(c3);
    cards.push_back(c3);
    cards.push_back(c3);
    cards.push_back(c3);
   list<Card>temp;
    while (!cards.empty())
    {
        int x = rand();
        x %= cards.size();
        list<Card>::iterator it = cards.begin();
        for (int j = 0; j < x; j++)
            it++;
        temp.push_back(*it);
        cards.erase(it);
    }
    cards = temp;
}

void Card:: setValue(int value){
    this->Value=value;
}
void Card::setName(string name) {
    this->Name=name;
}
int Card::getValue() {
    return Value;
}
string Card::getName() {
    return Name;
}

