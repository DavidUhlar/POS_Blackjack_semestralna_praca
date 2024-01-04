

#include "House.h"

House::House() : dealer(6)  {

}

void House::giveCard(Player& currentPlayer) {
    currentPlayer.addCard(this->dealer.handOutCard());
}

void House::giveCardSplit(Player& currentPlayer) {
    currentPlayer.addCardSplit(this->dealer.handOutCard());
}

void House::handingOutCards() {

    for (int i = 0; i < 2; ++i) {
        this->dealer.addCard(this->dealer.handOutCard());
        for (auto& players : listOfPlayers) {
            this->giveCard(*players);
        }
    }

}

void House::pushPlayer(unique_ptr<Player> player) {
    this->listOfPlayers.push_back(std::move(player));
}



void House::round() {
    cout << "velkost balicka: " << this->dealer.getGameDeckSize() << endl;
    for (auto& player: listOfPlayers) {
        player->makeDeposit();
    }


    int countBustSplitSize = 0;
    int countBustSplit = 0;

    cout << "" << endl;
    cout << "" << endl;
    cout << "----------TABLE-----------" << endl;
    if (this->dealer.getGameDeckSize() >= 60) {
        this->handingOutCards();
        this->dealer.printDeck(false);
        for (auto& player: listOfPlayers) {
            player->setBust(false, true);
            player->setBust(false, false);
            player->setFirstMove(false);
            player->printDeck();
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
        cout << "" << endl;
        cout << "Player: " << player->getName() << endl;

        string in;
        string inSplit;
        koniec = false;


        while (!koniec)
        {
            dealer.printDeck(false);
            player->printDeck();

            if (player->calculateValueOfHand() == 21) {
                cout << "BLACKJACK" << endl;
                koniec = true;
                break;
            }


            if (!player->getFirstMove()) {
                if (player->isSplitable()) {
                    cout << "hit/stand/surrender/split/doubleDown " << endl;
                } else {
                    cout << "hit/stand/surrender/doubleDown " << endl;
                }

            } else {
                cout << "hit/stand " << endl;
            }

            cin >> in;

            if (in == "hit") {
                if (player->hit(false)) {
                    this->giveCard(*player);
                }
                if (player->calculateValueOfHand() > 21) {

                    player->setBust(true, false);
                    cout << "bust " << endl;
                    koniec = true;
                } else if (player->calculateValueOfHand() == 21){
                    cout << "win " << endl;
                    koniec = true;
                }
            } else if (in == "stand") {
                koniec = true;
            } else if (in == "kys") {
                koniec = true;
            } else if (in == "split" && !player->getFirstMove() && player->isSplitable()) {

                player->split();
                countBustSplitSize++;
                bool koniecNormal = false;
                while (!koniecNormal)
                {
                    cout << "hand 1 " << endl;
                    player->printDeck();
                    cout << "hit/stand " << endl;

                    cin >> inSplit;
                    if (inSplit == "hit") {
                        if (player->hit(false)) {
                            this->giveCard(*player);
                        }
                        if (player->calculateValueOfHand() > 21) {

                            player->setBust(true, false);
                            cout << "bust " << endl;
                            koniecNormal = true;
                        } else if (player->calculateValueOfHand() == 21){
                            cout << "win " << endl;
                            koniecNormal = true;
                        }
                    } else if (inSplit == "stand") {
                        koniecNormal = true;
                    }
                }


                bool koniecSplit = false;
                while (!koniecSplit)
                {
                    cout << "hand 2 " << endl;
                    player->printDeckSplit();
                    cout << "hit/stand " << endl;

                    cin >> inSplit;
                    if (inSplit == "hit") {
                        if (player->hit(true)) {
                            this->giveCardSplit(*player);
                        }
                        if (player->calculateValueOfHandSplit() > 21) {

                            player->setBust(true, true);
                            cout << "bust " << endl;
                            koniecSplit = true;
                        } else if (player->calculateValueOfHandSplit() == 21){
                            cout << "win " << endl;
                            koniecSplit = true;
                        }
                    } else if (inSplit == "stand") {
                        koniecSplit = true;
                    }
                }
                koniec = true;
            } else if (in == "surrender" && !player->getFirstMove()) {
                player->surrender();
                koniec = true;

            } else if (in == "doubleDown" && !player->getFirstMove()) {
                player->doubleDown();
            } else {
                    cout << "wrong input " << endl;

            }

            if (!player->getFirstMove()) {
                player->setFirstMove(true);
            }

        }
        player->printDeck();
    }

    //posledne ked hraci dovyberaju
    this->dealer.printDeck(true);

    int countBust = 0;
    for (auto& player: listOfPlayers) {
        if (player->isBust(false)) {
            countBust++;
        }

        if (player->isBust(true)) {
            countBustSplit++;
        }

    }


    if ((countBustSplit == countBustSplitSize) && (countBustSplitSize > 0)) {
        cout << "DEALER WINS after split " << endl;
    }


    if (countBust == listOfPlayers.size()) {
        cout << "DEALER WINS" << endl;
    } else {
        while(this->dealer.calculateValueOfHand() < 17) {
            bool dealerWin = true;
            this->dealer.printDeck(true);
            for (auto& player: listOfPlayers) {
                if (this->dealer.calculateValueOfHand() < player->calculateValueOfHand() && !player->isBust(false)) {
                    dealerWin = false;
                }
                if (player->getIsHandSplit()) {
                    if (this->dealer.calculateValueOfHand() < player->calculateValueOfHandSplit() && !player->isBust(true)) {
                        dealerWin = false;
                    }
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
    cout << "end of game" << endl;

    this->getWinner(false);

    cout << "" << endl;
    cout << "Actuall balance: " << endl;
    for (auto& player: listOfPlayers) {
        cout << player->getName() << " " << player->getBalance() << endl;
    }

}



void House::getWinner(bool dealerWin) {
    cout << "" << endl;
    cout << "--------GAME RECAP---------" << endl;
    this->dealer.printDeck(true);
    for (auto& player: listOfPlayers) {
        player->printDeck();

        if (player->getIsHandSplit()) {
            player->printDeckSplit();
        }
    }

    cout << "" << endl;
    cout << "--------WINNERS---------" << endl;
    if (!dealerWin) {
        for (auto& player: listOfPlayers) {
            if (player->getIsHandSplit()) {
                cout << "Hand 1: " << endl;
            }
            if (player->calculateValueOfHand() > this->dealer.calculateValueOfHand() && !player->isBust(false)) {
                cout << player->getName() << " " << player->getDeposit() << " x2" << endl;
                cout <<  "Total win: " << (player->getDeposit()*2) << endl;

                player->updateBalance(player->getDeposit()*2);

                cout <<  "Total balance: " << (player->getBalance()) << endl;


            } else if (player->calculateValueOfHand() == this->dealer.calculateValueOfHand() && !player->isBust(false)) {
                cout << player->getName() << " " << player->getDeposit() << " x1" << endl;
                cout <<  "Total win: " << (player->getDeposit()) << endl;
                player->updateBalance(player->getDeposit());
                cout <<  "Total balance: " << (player->getBalance()) << endl;

            } else if (this->dealer.calculateValueOfHand() > 21 && !player->isBust(false)) {
                cout << player->getName() << " " << player->getDeposit() << " x2" << endl;
                cout <<  "Total win: " << (player->getDeposit()*2) << endl;

                player->updateBalance(player->getDeposit()*2);

                cout <<  "Total balance: " << (player->getBalance()) << endl;


            }

            //pre split

            if (player->getIsHandSplit()) {

                if (player->calculateValueOfHandSplit() > this->dealer.calculateValueOfHand() && !player->isBust(true)) {
                    cout << "Hand 2: " << endl;
                    cout << player->getName() << " " << player->getDeposit() << " x2" << endl;
                    cout <<  "Total win: " << (player->getDeposit()*2) << endl;

                    player->updateBalance(player->getDeposit()*2);

                    cout <<  "Total balance: " << (player->getBalance()) << endl;


                } else if (player->calculateValueOfHandSplit() == this->dealer.calculateValueOfHand() && !player->isBust(true)) {
                    cout << "Hand 2: " << endl;
                    cout << player->getName() << " " << player->getDeposit() << " x1" << endl;
                    cout <<  "Total win: " << (player->getDeposit()) << endl;
                    player->updateBalance(player->getDeposit());
                    cout <<  "Total balance: " << (player->getBalance()) << endl;

                } else if (this->dealer.calculateValueOfHand() > 21 && !player->isBust(true)) {
                    cout << "Hand 2: " << endl;
                    cout << player->getName() << " " << player->getDeposit() << " x2" << endl;
                    cout <<  "Total win: " << (player->getDeposit()*2) << endl;

                    player->updateBalance(player->getDeposit()*2);

                    cout <<  "Total balance: " << (player->getBalance()) << endl;


                }
            }
            player->setDeposit(0);

            cout << "" << endl;
        }
    } else {
        cout << "DEALER WINS" << endl;
    }

    for (auto& player: listOfPlayers) {
        player->removeCards();
    }
    this->dealer.removeCards();
}




House::~House() {

}



