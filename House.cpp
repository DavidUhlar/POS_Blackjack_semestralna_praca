

#include "House.h"

House::House() : dealer(6)  {

}

void House::giveCard(Player& currentPlayer) {
    currentPlayer.addCard(this->dealer.handOutCard());
}

void House::handingOutCards() {

    for (int i = 0; i < 2; ++i) {
        this->dealer.addCard(this->dealer.handOutCard());
        for (auto& players : listOfPlayers) {
            this->giveCard(players);
        }
    }

}

void House::pushPlayer(Player player) {
    this->listOfPlayers.push_back(player);
}



void House::round() {
    if (this->dealer.getGameDeckSize() >= 60) {
        this->handingOutCards();
        this->dealer.printDeck(false);
        for (auto& player: listOfPlayers) {

            player.printDeck();
        }
        this->numberOfRound++;
    } else {
        cout << "je koniec" << endl;
    }

    this->dealer.printDeck(true);
    while(this->dealer.hit()) {
        this->dealer.printDeck(true);
    }



    cout << "je koniec gamesky" << endl;
    this->dealer.printDeck(true);
}

int House::getNoRound() {
    return this->numberOfRound;
}


House::~House() {

}



