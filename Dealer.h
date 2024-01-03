#include "Card.h"
#include "GameDecks.h"


#ifndef SEMESTRALKA_DEALER_H
#define SEMESTRALKA_DEALER_H


class Dealer {
    public:
        Dealer(int numberOfDecks);
        std::unique_ptr<Card>  handOutCard();
        void addCard(std::unique_ptr<Card> card);
        void printDeck(bool showFirstCard);
        int getGameDeckSize();
        bool hit();
        int calculateValueOfHand();
        ~Dealer();

    private:
        int balance;
        std::vector<std::unique_ptr<Card>> dealerHand;
        GameDecks gameDecks;
        int valueOfHand;


};


#endif //SEMESTRALKA_DEALER_H
