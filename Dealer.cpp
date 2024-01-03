#include "Dealer.h"

Dealer::Dealer(int numberOfDecks) {
    this->gameDecks.loadDecks(numberOfDecks);
    this->gameDecks.shuffleDeck();
}

std::unique_ptr<Card> Dealer::handOutCard() {
    return std::move(this->gameDecks.deckPop());
}

void Dealer::addCard(std::unique_ptr<Card> card) {
    this->dealerHand.push_back(std::move(card));
}

void Dealer::printDeck(bool showFirstCard) {
    int index = 0;
    cout << "\nDealer: " << endl;
    this->calculateValueOfHand();

    for (const auto& card : this->dealerHand) {
        if (index == 0 && !showFirstCard) {
            cout << "Hidden Card" << endl;
        } else {
            cout << "Symbol: " << card->getSymbol() << " , Number: " << card->getNumber() <<  ", Value: " << card->getValue() << endl;
        }
        index++;
    }

    if (showFirstCard) {
        cout << "Value of Dealer's Hand: " << valueOfHand << endl;
    }
}

int Dealer::getGameDeckSize() {
    return this->gameDecks.getSizeOfDeck();
}

bool Dealer::hit() {
    if (this->calculateValueOfHand() < 17) {
        this->addCard(this->handOutCard());
        cout << "Dealer hits" << endl;
        return true;
    }
    cout << "Dealer stands" << endl;
    return false;
}

int Dealer::calculateValueOfHand() {
    valueOfHand = 0;
    for (const auto& card : this->dealerHand) {
        valueOfHand += card->getValue();
    }
    return valueOfHand;
}

Dealer::~Dealer() {
    // Unique pointers will automatically deallocate memory
}
