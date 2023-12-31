#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <filesystem>
#include "Card.h"
#include "GameDecks.h"

using namespace std;

int main() {

    GameDecks deck;
    deck.loadDecks(6);
    deck.shuffleDeck();
    deck.getSizeOfDeck();





    string unicodeString = "☺ Hello, Unicode! ✓ \u2660";

    cout << unicodeString << endl;


    return 0;
}
