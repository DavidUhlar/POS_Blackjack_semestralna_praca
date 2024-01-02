#include "Card.h"


Card::Card(string symbol, string number, int value) {
    this->symbol = symbol;
    this->number = number;
    this->value = value;

}




int Card::getValue() {
    return this->value;
}

Card::~Card() {

}

string Card::getSymbol() {
    return std::string();
}

string Card::getNumber() {
    return std::string();
}
