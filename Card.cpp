//
// Created by dadod on 30.12.2023.
//

#include "Card.h"

Card::Card(char symbol, char number, int value) {
    this->symbol = symbol;
    this->number = number;
    this->value = value;

}

char Card::getSymbol() {
    return this->symbol;
}

char Card::getNumber() {
    return this->number;
}

int Card::getValue() {
    return this->value;
}

Card::~Card() {

}
