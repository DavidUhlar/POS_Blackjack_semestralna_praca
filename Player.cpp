
#include "Player.h"

Player::Player(string name, int balance) {
    this->name = name;
    this->bust = false;
    this->balance = balance;
}

bool Player::hit() {
    if (calculateValueOfHand() >= 21) {
        return false;
    }
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

void Player::updateBalance(int balanceUpdate) {
    this->balance += balanceUpdate;
}

int Player::getBalance() {
    return this->balance;
}

void Player::addCard(Card* card) {
    this->hand.push_back(card);
}

void Player::removeCards() {
    this->hand.clear();
}
void Player::printDeck() {


    cout << "\n " << endl;
    cout << "Player " << this->name << ": " << endl;
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

    }
    cout << "Value of players hand: " << calculateValueOfHand() << endl;
}

int Player::calculateValueOfHand() {
    int valueOfHand = 0;

    for (auto card : this->hand) {
        valueOfHand += card->getValue();
    }
    return valueOfHand;
}

string Player::getName() {
    return this->name;
}

bool Player::isBust() {
    return this->bust;
}

void Player::setBust(bool value) {
    this->bust = value;
}

int Player::getDeposit() {
    return this->deposit;
}

bool Player::setDeposit(int newDeposit) {
    if ((this->balance - newDeposit >= 0) && (newDeposit > 0)) {
        this->deposit = newDeposit;
        this->balance -= this->deposit;
        return true;
    } else {
        return false;
    }

}

Player::~Player() {

}



