
#include "GameDecks.h"


GameDecks::GameDecks() {

}

void GameDecks::shuffleDeck() {


    mt19937 eng(time(NULL));
    shuffle(this->gameDeck.begin(), this->gameDeck.end(), eng);
}

void GameDecks::loadDecks(int numOfDecks) {

    filesystem::path currentPath = filesystem::current_path();
    filesystem::path fullPath = currentPath.parent_path() / "balicek.txt";
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


            this->gameDeck.push_back({new Card(symbol, number, value)});
        }
    }
}





int GameDecks::getSizeOfDeck() {
    cout << "velkost balicka: " << this->gameDeck.size() << endl;
    return this->gameDeck.size();
}

Card* GameDecks::deckPop() {
    //LIFO
    Card* lastCard = this->gameDeck.back();
    this->gameDeck.pop_back();
//    cout << lastCard->getSymbol() << lastCard->getNumber() << lastCard->getValue() << endl;
    return lastCard;
}

GameDecks::~GameDecks() {

}


