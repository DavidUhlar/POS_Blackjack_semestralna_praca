#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <filesystem>

using namespace std;

struct Card {
    string value;
    int quantity;
};

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
        int quantity;
        string value;


        getline(ss, token, ',');
        value = token;


        getline(ss, token);
        quantity = std::stoi(token);


        cards.push_back({value, quantity});

    }


    for (const auto& card : cards) {
        cout << "Value: " << card.value << ", Quantity: " << card.quantity << endl;
    }




    return 0;
}
