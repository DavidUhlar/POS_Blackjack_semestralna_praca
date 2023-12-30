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
        value = stoi(token);


        cards.push_back({symbol, number, value});

    }


    for (auto& card : cards) {
        if (card.getSymbol() == "S") {
            cout << "symbol: \u2660 , Number: " << card.getNumber() <<  ", value: " << card.getValue() << endl;
        } else if (card.getSymbol() == "H") {
            cout << "symbol: \u2665 , Number: " << card.getNumber() <<  ", value: " << card.getValue() << endl;
        } else if (card.getSymbol() == "D") {
            cout << "symbol: \u2666 , Number: " << card.getNumber() <<  ", value: " << card.getValue() << endl;
        } else if (card.getSymbol() == "C") {
            cout << "symbol: \u2663 , Number: " << card.getNumber() <<  ", value: " << card.getValue() << endl;
        }

    }



    string unicodeString = "☺ Hello, Unicode! ✓ \u2660";

    cout << unicodeString << endl;


    return 0;
}
