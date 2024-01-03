
#include "Player.h"
#include "Dealer.h"
//#include <vector>
//using namespace std;

#ifndef SEMESTRALKA_HOUSE_H
#define SEMESTRALKA_HOUSE_H

//class Player;
//class Dealer;

class House {
public:
    House();
    void giveCard(Player& player);
    void handingOutCards();
    int getNoRound();
    void round();
    void pushPlayer(std::unique_ptr<Player> player);
    ~House();
private:
    Dealer dealer;
    std::vector<std::unique_ptr<Player>> listOfPlayers;
    int numberOfRound;
};

#endif //SEMESTRALKA_HOUSE_H
