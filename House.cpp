

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
    cout << "velkost balicka: " << this->dealer.getGameDeckSize() << endl;
    this->makeDeposit();

    if (this->dealer.getGameDeckSize() >= 60) {
        this->handingOutCards();
        this->dealer.printDeck(false);
        for (auto& player: listOfPlayers) {
            player.setBust(false);
            player.printDeck();
        }
        this->numberOfRound++;
    } else {
        cout << "je koniec" << endl;
    }

    cout << "" << endl;
    cout << "" << endl;
    cout << "----------GAME-----------" << endl;
    cout << "" << endl;


    cout << "velkost balicka: " << this->dealer.getGameDeckSize() << endl;

    bool koniec = false;




    for (auto& player: listOfPlayers) {
        string in;
        koniec = false;

        while (!koniec)
        {
            dealer.printDeck(false);
            player.printDeck();

            if (player.calculateValueOfHand() == 21) {
                cout << "BLACKJACK" << endl;
                koniec = true;
                break;
            }

            cout << "hit/stand " << endl;
            cin >> in;

            if (in == "hit") {
                if (player.hit()) {
                    this->giveCard(player);
                }
                if (player.calculateValueOfHand() > 21) {

                    player.setBust(true);
                    cout << "bust " << endl;
                    koniec = true;
                } else if (player.calculateValueOfHand() == 21){
                    cout << "win " << endl;
                    koniec = true;
                }
            } else if (in == "stand") {
                koniec = true;
            } else if (in == "kys") {
                koniec = true;
            }
            else {
                cout << "wrong input " << endl;
            }

        }
        player.printDeck();
    }

    //posledne ked hraci dovyberaju
    this->dealer.printDeck(true);

    int countBust = 0;
    for (auto& player: listOfPlayers) {
        if (player.isBust()) {
            countBust++;
        }
    }

    if (countBust == listOfPlayers.size()) {
        cout << "DEALER WINS" << endl;
    } else {
        while(this->dealer.calculateValueOfHand() < 17) {
            bool dealerWin = true;
            this->dealer.printDeck(true);
            for (auto& player: listOfPlayers) {
                if (this->dealer.calculateValueOfHand() < player.calculateValueOfHand() && !player.isBust()) {
                    dealerWin = false;
                }
            }

            if (dealerWin) {
                cout << "DEALER WINS" << endl;
                this->getWinner(dealerWin);
                break;
            }
            this->dealer.hit();
            this->dealer.printDeck(true);
        }
    }
    cout << "je koniec gamesky" << endl;

    this->getWinner(false);

    cout << "" << endl;
    cout << "Actuall balance: " << endl;
    for (auto& player: listOfPlayers) {
        cout << player.getName() << " " << player.getBalance() << endl;
    }

}

int House::getNoRound() {
    return this->numberOfRound;
}

void House::getWinner(bool dealerWin) {
    cout << "" << endl;
    cout << "--------GAME RECAP---------" << endl;
    this->dealer.printDeck(true);
    for (auto& player: listOfPlayers) {
        player.printDeck();
    }

    cout << "" << endl;
    cout << "--------WINNERS---------" << endl;
    if (!dealerWin) {
        for (auto& player: listOfPlayers) {
            if (player.calculateValueOfHand() > this->dealer.calculateValueOfHand() && !player.isBust()) {
                cout << player.getName() << " " << player.getDeposit() << " x2" << endl;
                cout <<  "Total win: " << (player.getDeposit()*2) << endl;

                player.updateBalance(player.getDeposit()*2);

                cout <<  "Total balance: " << (player.getBalance()) << endl;

                player.setDeposit(0);
            } else if (player.calculateValueOfHand() == this->dealer.calculateValueOfHand() && !player.isBust()) {
                cout << player.getName() << " " << player.getDeposit() << " x1" << endl;
                cout <<  "Total win: " << (player.getDeposit()) << endl;
                player.updateBalance(player.getDeposit());
                cout <<  "Total balance: " << (player.getBalance()) << endl;
                player.setDeposit(0);
            } else if (this->dealer.calculateValueOfHand() > 21) {
                cout << player.getName() << " " << player.getDeposit() << " x2" << endl;
                cout <<  "Total win: " << (player.getDeposit()*2) << endl;

                player.updateBalance(player.getDeposit()*2);

                cout <<  "Total balance: " << (player.getBalance()) << endl;

                player.setDeposit(0);
            } else {
                player.setDeposit(0);
            }
            cout << "" << endl;
        }
    } else {
        cout << "DEALER WINS" << endl;
    }
}


void House::makeDeposit() {
    for (auto& player: listOfPlayers) {
        string in;
        bool koniec = false;
        while (!koniec) {
            cout << " " << endl;
            cout << "Player: " << player.getName() << endl;
            cout << "Select deposit (balance: " << player.getBalance() << "): " << endl;

            try {
                cin >> in;

                if (in == "koniec") {
                    koniec = true;
                }

                int deposit = stoi(in);
                if (player.setDeposit(deposit)) {
                    koniec = true;
                } else {
                    cout << "wrong input " << endl;
                }
            } catch (const exception& e) {
                cout << "wrong input " << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }
}

House::~House() {

}



