
#include "GameDecks.h"
#include <memory>
#include <filesystem>

GameDecks::GameDecks() {

}

void GameDecks::shuffleDeck() {


    mt19937 eng(time(NULL));
    shuffle(this->gameDeck.begin(), this->gameDeck.end(), eng);
}

void GameDecks::loadDecks(int numOfDecks) {

    filesystem::path currentPath = filesystem::current_path();
    filesystem::path fullPath = currentPath.parent_path() / "Server/balicek.txt";
    string fullPathStr = fullPath.string();
    cout << fullPathStr << endl;


    ifstream file(fullPathStr);


    if (!file.is_open()) {
        cerr << "Error opening file" << endl;

    }

    for (int i = 0; i < numOfDecks; ++i) {
        string line;
        file.clear();
        file.seekg(0, ios::beg);

        while (getline(file, line)) {
            stringstream ss(line);

            string token;
            string symbol;
            string number;
            int value;


            getline(ss, token, ',');
            symbol = token;
            getline(ss, token, ',');
            number = token;
            getline(ss, token);
            value = stoi(token);


            this->gameDeck.push_back(make_unique<Card>(symbol, number, value));
        }
    }
}





int GameDecks::getSizeOfDeck() {
    return this->gameDeck.size();
}

unique_ptr<Card> GameDecks::deckPop() {
    //LIFO
    unique_ptr<Card> lastCard = std::move(this->gameDeck.back());
    this->gameDeck.pop_back();
    return lastCard;
}

GameDecks::~GameDecks() {

}


