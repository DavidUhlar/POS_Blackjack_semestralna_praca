#include <memory>

#include "Card.h"
#include "GameDecks.h"


#ifndef SEMESTRALKA_DEALER_H
#define SEMESTRALKA_DEALER_H

using namespace std;

class Dealer {
    public:
        Dealer(int numberOfDecks);
        unique_ptr<Card> handOutCard();
        void addCard(unique_ptr<Card> card);
        void printDeck(bool showFirstCard);
        int getGameDeckSize();
        void hit();
        int calculateValueOfHand();
        void aceChange();
        void removeCards();
        ~Dealer();

    private:
        vector<unique_ptr<Card>> dealerHand;
        GameDecks gameDecks;
        int valueOfHand;


};


#endif //SEMESTRALKA_DEALER_H
