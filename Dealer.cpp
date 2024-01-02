
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

void Dealer::printDeck(int rounds) {
    int valueOfHand = 0;
    int index = 0;
    cout << "rounds: " << rounds << endl;
    for (auto card : this->dealerHand) {
//        if (index == 0 && rounds == )

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
        index++;
    }
    cout << "Value of hand: " << valueOfHand << endl;
}

int Dealer::getGameDeckSize() {
    return this->gameDecks.getSizeOfDeck();
}

Dealer::~Dealer() {

}
