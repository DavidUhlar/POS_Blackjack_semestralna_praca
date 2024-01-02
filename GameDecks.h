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

        Card* deckPop();
        ~GameDecks();

    private:
        vector<Card*> gameDeck;

};


#endif //SEMESTRALKA_GAMEDECKS_H
