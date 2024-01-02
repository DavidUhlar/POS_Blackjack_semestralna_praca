

#include "Card.h"
#include <vector>
#include <iostream>

#ifndef SEMESTRALKA_PLAYER_H
#define SEMESTRALKA_PLAYER_H

class Player {
public:
    Player();
    bool hit();
    bool stand();
    bool doubleDown();
    bool split();
    bool surrender();
    void updateBalance();
    int getBalance();
    void addCard(Card* card);
    void removeCards();
    void printDeck();
    ~Player();

private:
    vector<Card*> hand;
    int balance;


};


#endif //SEMESTRALKA_PLAYER_H
