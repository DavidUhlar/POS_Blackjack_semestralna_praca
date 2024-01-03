

#include "Card.h"
#include <vector>
#include <iostream>

#ifndef SEMESTRALKA_PLAYER_H
#define SEMESTRALKA_PLAYER_H

class Player {
public:
    Player(string name, int balance);
    bool hit();
    bool doubleDown();
    bool split();
    bool surrender();
    void updateBalance(int balanceUpdate);
    int getBalance();
    void addCard(Card* card);
    void removeCards();
    void printDeck();
    int calculateValueOfHand();
    string getName();
    bool isBust();
    void setBust(bool value);
    int getDeposit();
    bool setDeposit(int newDeposit);
    ~Player();

private:
    vector<Card*> hand;
    int balance;
    int deposit;
    string name;
    bool bust;

};


#endif //SEMESTRALKA_PLAYER_H
