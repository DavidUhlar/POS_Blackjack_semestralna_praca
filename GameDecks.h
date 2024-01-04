#include "Card.h"
#include <vector>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <sstream>
#include <random>
#include <algorithm>
#include <memory>

#ifndef SEMESTRALKA_GAMEDECKS_H
#define SEMESTRALKA_GAMEDECKS_H

using namespace std;

class GameDecks {

    public:
        GameDecks();
        void shuffleDeck();
        void loadDecks(int numOfDecks);
        int getSizeOfDeck();

        unique_ptr<Card> deckPop();
        ~GameDecks();

    private:
        vector<unique_ptr<Card>> gameDeck;

};


#endif //SEMESTRALKA_GAMEDECKS_H
