#include "Card.h"
#include <vector>

#ifndef SEMESTRALKA_PLAYER_H
#define SEMESTRALKA_PLAYER_H


class Player {

public:
    Player();
    void hit();
    void stand();
    void doubleDown();
    void split();
    void surrender();
    void updateBalance();
    int getBalance();
    ~Player();

private:
    vector<Card*> hand;

};


#endif //SEMESTRALKA_PLAYER_H
