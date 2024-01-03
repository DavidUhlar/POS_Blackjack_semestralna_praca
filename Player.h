

#include "Card.h"
#include <vector>
#include <iostream>
#include <memory>

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
    void addCard(std::unique_ptr<Card> card);
    void removeCards();
    void printDeck();
    ~Player();

private:
    std::vector<std::unique_ptr<Card>> hand;
    int balance;


};


#endif //SEMESTRALKA_PLAYER_H
