//
// Created by dadod on 30.12.2023.
//

#include "Card.h"


Card::Card(string symbol, string number, int value) {
    this->symbol = symbol;
    this->number = number;
    this->value = value;

}

string Card::getSymbol() {
    return this->symbol;
}

string Card::getNumber() {
    return this->number;
}

int Card::getValue() {
    return this->value;
}

Card::~Card() {

}
