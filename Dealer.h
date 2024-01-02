#include "Card.h"
#include "GameDecks.h"
#include "House.h"

#ifndef SEMESTRALKA_DEALER_H
#define SEMESTRALKA_DEALER_H


class Dealer {
    public:
        Dealer(int numberOfDecks);

    Dealer();

    Card* handOutCard();
        void addCard(Card* card);
        void printDeck(int rounds);
        int getGameDeckSize();
        ~Dealer();

    private:
        int balance;
        vector<Card*> dealerHand;
        GameDecks gameDecks;


};


#endif //SEMESTRALKA_DEALER_H
