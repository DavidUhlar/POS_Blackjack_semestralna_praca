#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <filesystem>
#include "Card.h"

using namespace std;

int main() {
    vector<Card> cards;
    string line;

    filesystem::path currentPath = filesystem::current_path();
    filesystem::path fullPath = currentPath.parent_path() / "balicek.txt";
    string fullPathStr = fullPath.string();
    cout << fullPathStr << endl;


    ifstream file(fullPathStr);


    if (!file.is_open()) {
        cerr << "Error opening file" << endl;
        return 1;
    }

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
        value = std::stoi(token);


        cards.push_back({symbol, number, value});

    }


    for (auto& card : cards) {
        cout << "symbol: " << card.getSymbol() << ", Quantity: " << card.getNumber() <<  ", value: " << card.getValue() << endl;
    }


    std::string unicodeString = u8"☺ Hello, Unicode! ✓";

    std::cout << unicodeString << std::endl;


    return 0;
}
