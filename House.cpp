#include "House.h"

House::House() : dealer(6) {}

void House::giveCard(Player& currentPlayer) {
    currentPlayer.addCard(this->dealer.handOutCard());
}

void House::handingOutCards() {
    for (int i = 0; i < 2; ++i) {
        dealer.addCard(dealer.handOutCard());
        for (auto &player: listOfPlayers) {
            giveCard(*player); // Dereference the unique_ptr
        }
    }
}

void House::pushPlayer(std::unique_ptr<Player> player) {
    listOfPlayers.push_back(std::move(player));
}

void House::round() {
    if (dealer.getGameDeckSize() < 60) {
        cout << "Insufficient cards to start a new round." << endl;
        return;
    }

    handingOutCards();
    dealer.printDeck(false);

    for (auto& player : listOfPlayers) {
        player->printDeck(); // Ensure printDeck is compatible with the pointer
    }

    numberOfRound++;

    dealer.printDeck(true);
    while (dealer.hit()) {
        dealer.printDeck(true);
    }

    cout << "End of the round." << endl;
    dealer.printDeck(true);
}

House::~House() {}

// Additional implementations ...
