
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

void Player::addCard(std::unique_ptr<Card> card) {
    hand.push_back(std::move(card));
}

void Player::removeCards() {
    this->hand.clear();
}
void Player::printDeck() {
    int valueOfHand = 0;

    cout << "\n " << endl;
    cout << "Player: " << endl;
    for (auto& card : this->hand) {
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
    cout << "Value of players hand: " << valueOfHand << endl;
}



Player::~Player() {

}
