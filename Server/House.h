
#include "Player.h"
#include "Dealer.h"
#include <memory>


#ifndef SEMESTRALKA_HOUSE_H
#define SEMESTRALKA_HOUSE_H



class House {
public:
    House();
    void giveCard(Player& player);
    void giveCardSplit(Player& player);
    void handingOutCards();
    void round();
    void pushPlayer(unique_ptr<Player> player);
    void getWinner(bool dealerWin);

    ~House();
private:
    Dealer dealer;
    vector<unique_ptr<Player>> listOfPlayers;
    int numberOfRound;
};

#endif //SEMESTRALKA_HOUSE_H
