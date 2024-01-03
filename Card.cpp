#include "Card.h"


Card::Card(string symbol, string number, int value) {
    this->symbol = symbol;
    this->number = number;
    this->value = value;

}

int Card::getValue() {
    return this->value;
}



string Card::getSymbol() {
    return this->symbol;
}

string Card::getNumber() {
    return this->number;
}


void Card::setValue(int newValue) {
    this->value = newValue;
}


Card::~Card() {

}

