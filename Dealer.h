#include "Card.h"
#include "GameDecks.h"


#ifndef SEMESTRALKA_DEALER_H
#define SEMESTRALKA_DEALER_H


class Dealer {
    public:
        Dealer(int numberOfDecks);
        Card* handOutCard();
        void addCard(Card* card);
        void printDeck(bool showFirstCard);
        int getGameDeckSize();
        void hit();
        int calculateValueOfHand();
        ~Dealer();

    private:
        int balance;
        vector<Card*> dealerHand;
        GameDecks gameDecks;
        int valueOfHand;


};


#endif //SEMESTRALKA_DEALER_H
