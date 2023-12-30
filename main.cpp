#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <filesystem>

struct Card {
    std::string value;
    int quantity;
};

int main() {
    std::vector<Card> cards;
    std::string line;

    std::filesystem::path currentPath = std::filesystem::current_path();
    std::filesystem::path fullPath = currentPath.parent_path() / "balicek.txt";
    std::string fullPathStr = fullPath.string();
    std::cout << fullPathStr << std::endl;


    std::ifstream file(fullPathStr);


    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string token;
        int quantity;
        std::string value;


        getline(ss, token, ',');
        value = token;


        getline(ss, token);
        quantity = std::stoi(token);


        cards.push_back({value, quantity});

    }


    for (const auto& card : cards) {
        std::cout << "Value: " << card.value << ", Quantity: " << card.quantity << std::endl;
    }




    return 0;
}
