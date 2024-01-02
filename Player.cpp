
#include "Player.h"

Player::Player() {

}

bool Player::hit() {
    return true;
}

bool Player::stand() {
    return true;
}

bool Player::doubleDown() {
    return true;
}

bool Player::split() {
    return true;
}

bool Player::surrender() {
    return true;
}

void Player::updateBalance() {

}

int Player::getBalance() {
    return 1;
}

void Player::addCard(Card* card) {
    this->hand.push_back(card);
}

void Player::removeCards() {
    hand.clear();
}
void Player::printDeck() {
    int valueOfHand = 0;
    for (auto card : this->hand) {
        if (card->getSymbol() == "S") {
            cout << "symbol: \u2660 , Number: " << card->getNumber() <<  ", value: " << card->getValue() << endl;
        } else if (card->getSymbol() == "H") {
            cout << "symbol: \u2665 , Number: " << card->getNumber() <<  ", value: " << card->getValue() << endl;
        } else if (card->getSymbol() == "D") {
            cout << "symbol: \u2666 , Number: " << card->getNumber() <<  ", value: " << card->getValue() << endl;
        } else if (card->getSymbol() == "C") {
            cout << "symbol: \u2663 , Number: " << card->getNumber() <<  ", value: " << card->getValue() << endl;
        }
        valueOfHand += card->getValue();
    }
    cout << "Value of hand: " << valueOfHand << endl;
}



Player::~Player() {

}
