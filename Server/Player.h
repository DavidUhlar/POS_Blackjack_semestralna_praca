

#include "Card.h"
#include <vector>
#include <iostream>
#include <memory>
#include <limits>

#ifndef SEMESTRALKA_PLAYER_H
#define SEMESTRALKA_PLAYER_H

class Player {
public:
    Player(string name, int balance);
    bool hit(bool isSplit);
    bool doubleDown();
    bool isSplitable();
    void split();
    void surrender();
    void updateBalance(int balanceUpdate);
    int getBalance();
    void addCard(unique_ptr<Card> card);
    void addCardSplit(unique_ptr<Card> card);
    void removeCards();
    void printDeck();
    void printDeckSplit();
    int calculateValueOfHand();
    int calculateValueOfHandSplit();
    string getName();
    bool isBust(bool isSplit);
    void setBust(bool value, bool isSplit);
    int getDeposit();
    bool setDeposit(int newDeposit);
    void aceChange(bool isSplit);
    bool getFirstMove();
    void setFirstMove(bool newFirstMove);
    bool getIsHandSplit();
    void makeDeposit();
    ~Player();

private:
    vector<unique_ptr<Card>> hand;
    int balance;
    int deposit;
    string name;
    bool bust;
    bool bustSplit;
    vector<unique_ptr<Card>> splitHand;
    bool firstMove;
    bool isHandSplit;


};


#endif //SEMESTRALKA_PLAYER_H
