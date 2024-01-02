
#include "GameDecks.h"


GameDecks::GameDecks() {
    this->gameDeck;
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

void GameDecks::getSizeOfDeck() {
    for (auto card : this->gameDeck) {
        if (card->getSymbol().compare("S")) {
            cout << "symbol: \u2660 , Number: " << card->getNumber() <<  ", value: " << card->getValue() << endl;
        } else if (card->getSymbol().compare("H")) {
            cout << "symbol: \u2665 , Number: " << card->getNumber() <<  ", value: " << card->getValue() << endl;
        } else if (card->getSymbol().compare("D")) {
            cout << "symbol: \u2666 , Number: " << card->getNumber() <<  ", value: " << card->getValue() << endl;
        } else if (card->getSymbol().compare("C")) {
            cout << "symbol: \u2663 , Number: " << card->getNumber() <<  ", value: " << card->getValue() << endl;
        }

    }
    cout << "velkost balicka: " << this->gameDeck.size() << endl;
}
GameDecks::~GameDecks() {

}