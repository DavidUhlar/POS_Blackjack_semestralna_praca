#include "Card.h"
#include <vector>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <sstream>
#include <random>
#include <algorithm>


#ifndef SEMESTRALKA_GAMEDECKS_H
#define SEMESTRALKA_GAMEDECKS_H

using namespace std;

class GameDecks {

    public:
        GameDecks();
        void shuffleDeck();
        void loadDecks(int numOfDecks);
        int getSizeOfDeck();

    std::unique_ptr<Card>  deckPop();
        ~GameDecks();

    private:
    std::vector<std::unique_ptr<Card>> gameDeck;

};


#endif //SEMESTRALKA_GAMEDECKS_H
