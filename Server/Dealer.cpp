
#include "Dealer.h"



Dealer::Dealer(int numberOfDecks) {
    this->gameDecks.loadDecks(numberOfDecks);
    this->gameDecks.shuffleDeck();
}

unique_ptr<Card> Dealer::handOutCard() {
    return this->gameDecks.deckPop();
}

void Dealer::addCard(unique_ptr<Card> card) {
    this->dealerHand.push_back(std::move(card));
    this->aceChange();
}

string Dealer::printDeck(bool showFirstCard) {
    string cards = "";
    int index = 0;

    cout << "\n " << endl;
    cout << "Dealer: " << endl;
    cards += "\n ";
    cards += "Dealer : \n";


    this->calculateValueOfHand();

    for (auto& card : this->dealerHand) {
        if (showFirstCard) {

            if (card->getSymbol() == "S") {
                cout << "symbol: \u2660 , Number: " << card->getNumber() <<  ", value: " << card->getValue() << endl;
                cards += "symbol: S , Number: " + card->getNumber() +  ", value: " + to_string(card->getValue()) + "\n";
            } else if (card->getSymbol() == "H") {
                cout << "symbol: \u2665 , Number: " << card->getNumber() <<  ", value: " << card->getValue() << endl;
                cards += "symbol: H , Number: " + card->getNumber() +  ", value: " + to_string(card->getValue()) + "\n";
            } else if (card->getSymbol() == "D") {
                cout << "symbol: \u2666 , Number: " << card->getNumber() <<  ", value: " << card->getValue() << endl;
                cards += "symbol: D , Number: " + card->getNumber() +  ", value: " + to_string(card->getValue()) + "\n";
            } else if (card->getSymbol() == "C") {
                cout << "symbol: \u2663 , Number: " << card->getNumber() <<  ", value: " << card->getValue() << endl;
                cards += "symbol: C , Number: " + card->getNumber() +  ", value: " + to_string(card->getValue()) + "\n";
            }


        } else {

            if (index == 0) {
                cout << "hidden card" << endl;
                cards += "hidden card\n";
            } else {
                if (card->getSymbol() == "S") {
                    cout << "symbol: \u2660 , Number: " << card->getNumber() <<  ", value: " << card->getValue() << endl;
                    cards += "symbol: S , Number: " + card->getNumber() +  ", value: " + to_string(card->getValue()) + "\n";
                } else if (card->getSymbol() == "H") {
                    cout << "symbol: \u2665 , Number: " << card->getNumber() <<  ", value: " << card->getValue() << endl;
                    cards += "symbol: H , Number: " + card->getNumber() +  ", value: " + to_string(card->getValue()) + "\n";
                } else if (card->getSymbol() == "D") {
                    cout << "symbol: \u2666 , Number: " << card->getNumber() <<  ", value: " << card->getValue() << endl;
                    cards += "symbol: D , Number: " + card->getNumber() +  ", value: " + to_string(card->getValue()) + "\n";
                } else if (card->getSymbol() == "C") {
                    cout << "symbol: \u2663 , Number: " << card->getNumber() <<  ", value: " << card->getValue() << endl;
                    cards += "symbol: C , Number: " + card->getNumber() +  ", value: " + to_string(card->getValue()) + "\n";
                }
            }
        }

        index++;

    }
    if (showFirstCard) {
        cout << "Value of dealers hand: " << valueOfHand << endl;
        cards += "Value of dealers hand: " + to_string(valueOfHand) + "\n";
    }
    return cards;
}



int Dealer::getGameDeckSize() {
    return this->gameDecks.getSizeOfDeck();
}



void Dealer::hit() {
    this->addCard(this->handOutCard());
}

int Dealer::calculateValueOfHand() {
    this->valueOfHand = 0;

    for (auto& card : this->dealerHand) {
        this->valueOfHand += card->getValue();
    }


    return this->valueOfHand;
}

void Dealer::aceChange() {
    if (this->calculateValueOfHand() > 21) {
        for (auto& card : this->dealerHand) {
            if (this->calculateValueOfHand() > 21) {
                if ((card->getNumber() == "A") && (card->getValue() == 11)) {
                    card->setValue(1);
                }
            }

        }
    }

    this->calculateValueOfHand();
}

void Dealer::removeCards() {
    this->dealerHand.clear();
    this->valueOfHand = 0;

}

Dealer::~Dealer() {

}



