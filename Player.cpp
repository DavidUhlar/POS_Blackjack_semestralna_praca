

#include "Player.h"

Player::Player(string name, int balance) {
    this->name = name;
    this->bust = false;
    this->bustSplit = false;
    this->balance = balance;
    this->firstMove = false;
    this->isHandSplit = false;
}


bool Player::hit(bool isSplit) {
    if (!isSplit) {
        if (this->calculateValueOfHand() >= 21) {
            return false;
        }
        return true;
    } else {
        if (this->calculateValueOfHandSplit() >= 21) {
            return false;
        }
        return true;
    }
}


bool Player::doubleDown() {
    if (this->getBalance() - this->getDeposit() >= 0) {
        this->balance = this->balance - this->getDeposit();
        this->deposit = this->deposit*2;
        return true;
    } else {
        cout << "cannot double down" << endl;
        return false;
    }

}



bool Player::isSplitable() {
    if ((this->hand.at(0)->getValue() == this->hand.at(1)->getValue()) && this->balance >= this->deposit) {
        return true;
    } else {
        return false;
    }
}

void Player::split() {
    unique_ptr<Card> lastCard = std::move(this->hand.back());
    this->hand.pop_back();
    this->splitHand.push_back(std::move(lastCard));
    this->balance -= deposit;
    this->isHandSplit = true;


}

void Player::surrender() {
    int vypocet = this->getDeposit()/2;
    this->updateBalance(vypocet);


}

void Player::updateBalance(int balanceUpdate) {
    this->balance += balanceUpdate;
}

int Player::getBalance() {
    return this->balance;
}

void Player::addCard(unique_ptr<Card> card) {
    this->hand.push_back(std::move(card));
    this->aceChange(false);
}
void Player::addCardSplit(unique_ptr<Card> card) {
    this->splitHand.push_back(std::move(card));
    this->aceChange(true);
}

void Player::removeCards() {
    this->hand.clear();
    this->splitHand.clear();
    this->isHandSplit = false;
    this->bust = false;
    this->bustSplit = false;
    this->firstMove = false;
    this->deposit = 0;
}
void Player::printDeck() {


    cout << "\n " << endl;
    cout << "Player " << this->name << ": " << endl;
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

    }
    cout << "Value of players hand: " << calculateValueOfHand() << endl;
}

void Player::printDeckSplit() {


    cout << "\n " << endl;
    cout << "Player " << this->name << ": " << endl;
    for (auto& card : this->splitHand) {
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
    cout << "Value of players hand: " << calculateValueOfHandSplit() << endl;
}

int Player::calculateValueOfHand() {
    int valueOfHand = 0;

    for (auto& card : this->hand) {
        valueOfHand += card->getValue();
    }
    return valueOfHand;
}

int Player::calculateValueOfHandSplit() {
    int valueOfHand = 0;

    for (auto& card : this->splitHand) {
        valueOfHand += card->getValue();
    }
    return valueOfHand;
}

string Player::getName() {
    return this->name;
}

bool Player::isBust(bool isSplit) {
    if (!isSplit) {
        return this->bust;
    } else {
        return this->bustSplit;
    }

}

void Player::setBust(bool value, bool isSplit) {

    if (!isSplit) {
        this->bust = value;
    } else {
        this->bustSplit = value;
    }
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

void Player::aceChange(bool isSplit) {
    if (!isSplit) {
        if (this->calculateValueOfHand() > 21) {
            for (auto& card : this->hand) {
                if (this->calculateValueOfHand() > 21) {
                    if ((card->getNumber() == "A") && (card->getValue() == 11)) {
                        card->setValue(1);
                    }
                }

            }
        }
    } else {
        if (this->calculateValueOfHandSplit() > 21) {
            for (auto& card : this->splitHand) {
                if (this->calculateValueOfHandSplit() > 21) {
                    if ((card->getNumber() == "A") && (card->getValue() == 11)) {
                        card->setValue(1);
                    }
                }

            }
        }
    }
    this->calculateValueOfHand();
    this->calculateValueOfHandSplit();
}

bool Player::getFirstMove() {
    return this->firstMove;
}

void Player::setFirstMove(bool newFirstMove) {
    this->firstMove = newFirstMove;
}

bool Player::getIsHandSplit() {
    return this->isHandSplit;
}

void Player::makeDeposit() {
        string in;
        bool koniec = false;
        while (!koniec) {
            cout << " " << endl;
            cout << "Player: " << this->getName() << endl;
            cout << "Select deposit(10/20/100) (balance: " << this->getBalance() << "): " << endl;
            cout << "Leave with: leave " << endl;

            try {
                cin >> in;

                if (in == "leave") {
                    koniec = true;
                }

                int depositLocal = stoi(in);

                if (depositLocal == 10 || depositLocal == 20 || depositLocal == 100) {
                    if (depositLocal <= this->getBalance()) {
                        if (this->setDeposit(depositLocal)) {
                            koniec = true;
                        } else {
                            cout << "wrong input " << endl;
                        }
                    } else {
                        cout << "not enough tokens on account " << endl;
                    }
                } else {
                    cout << "House only accepts 10/20/100 tokens " << endl;
                }
            } catch (const exception& e) {
                cout << "wrong input " << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }

}

Player::~Player() {

}



