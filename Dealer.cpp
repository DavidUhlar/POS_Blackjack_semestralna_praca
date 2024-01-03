
#include "Dealer.h"



Dealer::Dealer(int numberOfDecks) {
    this->gameDecks.loadDecks(numberOfDecks);
    this->gameDecks.shuffleDeck();
}

Card *Dealer::handOutCard() {
    return this->gameDecks.deckPop();
}

void Dealer::addCard(Card *card) {
    this->dealerHand.push_back(card);
}

void Dealer::printDeck(bool showFirstCard) {

    int index = 0;

    cout << "\n " << endl;
    cout << "Dealer: " << endl;



    this->calculateValueOfHand();

    for (auto card : this->dealerHand) {
        if (showFirstCard) {

            if (card->getSymbol() == "S") {
                cout << "symbol: \u2660 , Number: " << card->getNumber() <<  ", value: " << card->getValue() << endl;
            } else if (card->getSymbol() == "H") {
                cout << "symbol: \u2665 , Number: " << card->getNumber() <<  ", value: " << card->getValue() << endl;
            } else if (card->getSymbol() == "D") {
                cout << "symbol: \u2666 , Number: " << card->getNumber() <<  ", value: " << card->getValue() << endl;
            } else if (card->getSymbol() == "C") {
                cout << "symbol: \u2663 , Number: " << card->getNumber() <<  ", value: " << card->getValue() << endl;
            }


        } else {

            if (index == 0) {
                cout << "tajnô karta " << endl;
            } else {
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
        }

        index++;

    }
    if (showFirstCard) {
        cout << "Value of dealers hand: " << valueOfHand << endl;
    }

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


Dealer::~Dealer() {

}