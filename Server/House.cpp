

#include <thread>
#include "House.h"


House::House(const char *ipAddress, int port) : dealer(6)  {
    // Create socket
    this->serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    // Set up server address struct
    memset(&serverAddr, 0, sizeof(this->serverAddr));
    this->serverAddr.sin_family = AF_INET;
    this->serverAddr.sin_port = htons(port);

    // Set the IP address to the desired value
    inet_pton(AF_INET, ipAddress, &(this->serverAddr.sin_addr));

    // Bind socket to address
    bind(this->serverSocket, (struct sockaddr*)&serverAddr, sizeof(this->serverAddr));

    // Listen for incoming connections
    listen(this->serverSocket, 5);

    // Accept connection
    this->clientAddrLen = sizeof(clientAddr);
    this->clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);
}

void House::sendMessageToClient(const std::string& message) {
    if (send(clientSocket, message.c_str(), message.size(), 0) == -1) {
        std::cerr << "Failed to send message to client." << std::endl;
    }
}

string House::receiveInputFromClient() {
    std::string input = "";
    char buffer[1024];

    memset(buffer, 0, sizeof(buffer));

    // Receive data from client
    recv(this->clientSocket, buffer, sizeof(buffer), 0);
    input += buffer;

    return input;
}

void House::makeDeposit(Player& player) {
    string in;
    bool koniec = false;
    while (!koniec) {
        cout << " " << endl;
        cout << "Player: " << player.getName() << endl;
        cout << "Select deposit(10/20/100) (balance: " << player.getBalance() << "): " << endl;
        this->sendMessageToClient(" \n");
        this->sendMessageToClient("Player:  ");
        this->sendMessageToClient(player.getName() + "\n");
        this->sendMessageToClient("Select deposit(10/20/100) (balance: " );
        this->sendMessageToClient(to_string(player.getBalance()));
        this->sendMessageToClient("): ;");
        //        cout << "Leave with: leave " << endl;

        try {
//            cin >> in;
            this->sendMessageToClient("specialMessage");
            in = this->receiveInputFromClient();

            if (in == "leave") {
                koniec = true;
            }

            int depositLocal = stoi(in);

            if (depositLocal == 10 || depositLocal == 20 || depositLocal == 100) {
                if (depositLocal <= player.getBalance()) {
                    if (player.setDeposit(depositLocal)) {
                        koniec = true;
                    } else {
                      cout << "wrong input " << endl;
                        this->sendMessageToClient("wrong input ");
                    }
                } else {
                    cout << "not enough tokens on account " << endl;
                    this->sendMessageToClient("not enough tokens on account ");
                }
            } else {
                cout << "House only accepts 10/20/100 tokens " << endl;
                this->sendMessageToClient("House only accepts 10/20/100 tokens ");
            }
        } catch (const exception& e) {
            cout << "wrong input " << endl;
            this->sendMessageToClient("wrong input ");
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

}

void House::receiveName() {
    std::string name = "";
    char buffer[1024];

    memset(buffer, 0, sizeof(buffer));

    // Receive data from client
    recv(this->clientSocket, buffer, sizeof(buffer), 0);
    name += buffer;
    std::cout << "Received name: " << buffer << std::endl;
    std::cout << "Received string name: " << name << std::endl;


    std::stringstream ss(buffer);
    int balance = 0;
    std::getline(ss, name, ';');
    ss >> balance;

    cout << "name: " << name << endl;
    cout << "balance: " << balance << endl;


    auto regina = std::make_unique<Player>(name, balance);
    this->pushPlayer(std::move(regina));

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
    this->listOfPlayers.emplace_back(std::move(player));
}


void House::round() {
    cout << "velkost balicka: " << this->dealer.getGameDeckSize() << endl;
    for (auto& player: listOfPlayers) {
        this->makeDeposit(*player);
    }


//std::vector<std::thread> bettingThreads;
//
//    // Launch a thread for each player to place their bets
//    for (auto& player : listOfPlayers) {
//        bettingThreads.emplace_back(&Player::makeDeposit, player.get());
//    }
//
//    // Wait for all the betting threads to finish
//    for (auto& t : bettingThreads) {
//        if (t.joinable()) {
//            t.join();
//        }
//    }



    int countBustSplitSize = 0;
    int countBustSplit = 0;

    cout << "" << endl;
    cout << "" << endl;
    cout << "----------TABLE-----------" << endl;
    this->sendMessageToClient("\n");
    this->sendMessageToClient("\n");
    this->sendMessageToClient("----------TABLE-----------\n");
    if (this->dealer.getGameDeckSize() >= 60) {
        this->handingOutCards();
       string kokot = this->dealer.printDeck(false);
        this->sendMessageToClient(this->dealer.printDeck(false));
        cout << "frajerina: " << kokot << endl;
        for (auto& player: listOfPlayers) {
            player->setBust(false, true);
            player->setBust(false, false);
            player->setFirstMove(false);
            player->printDeck();
            this->sendMessageToClient(player->printDeck());
        }
        this->numberOfRound++;
    } else {
        cout << "je koniec" << endl;
    }

    cout << "" << endl;
    cout << "" << endl;
    cout << "----------GAME-----------" << endl;
    cout << "" << endl;

    this->sendMessageToClient("\n\n ----------GAME-----------\n");

    bool koniec = false;

    for (auto& player: listOfPlayers) {
        cout << "" << endl;
        cout << "Player: " << player->getName() << endl;

        string in;
        string inSplit;
        koniec = false;


        while (!koniec)
        {
            this->sendMessageToClient( dealer.printDeck(false));
            this->sendMessageToClient( player->printDeck());

            if (player->calculateValueOfHand() == 21) {
                cout << "BLACKJACK" << endl;
                this->sendMessageToClient("BLACKJACK");
                koniec = true;
                break;
            }


            if (!player->getFirstMove()) {
                if (player->isSplitable()) {
                    cout << "hit/stand/surrender/split/doubleDown " << endl;
                    this->sendMessageToClient( "hit/stand/surrender/split/doubleDown ;");
                    this->sendMessageToClient("specialMessageMove");
                } else {
                    cout << "hit/stand/surrender/doubleDown " << endl;
                    this->sendMessageToClient( "hit/stand/surrender/doubleDown ;");
                    this->sendMessageToClient("specialMessageMove");
                }

            } else {
                cout << "hit/stand " << endl;
                this->sendMessageToClient( "hit/stand ;");
                this->sendMessageToClient("specialMessageMove");
            }

//            cin >> in;
            in = this->receiveInputFromClient();

            if (in == "hit") {
                if (player->hit(false)) {
                    this->giveCard(*player);
                }
                if (player->calculateValueOfHand() > 21) {

                    player->setBust(true, false);
                    cout << "bust " << endl;
                    this->sendMessageToClient("bust ");
                    koniec = true;
                } else if (player->calculateValueOfHand() == 21){
                    cout << "win " << endl;
                    this->sendMessageToClient("win ");
                    koniec = true;
                }
            } else if (in == "stand") {
                koniec = true;
            } else if (in == "end") {
                koniec = true;
            } else if (in == "split" && !player->getFirstMove() && player->isSplitable()) {

                player->split();
                countBustSplitSize++;
                bool koniecNormal = false;
                while (!koniecNormal)
                {
                    cout << "hand 1 " << endl;
                    this->sendMessageToClient("hand 1 \n");
                    this->sendMessageToClient(player->printDeck());

                    cout << "hit/stand " << endl;
                    this->sendMessageToClient("hit/stand \n");
                    this->sendMessageToClient(";specialMessageMove");


//                    cin >> inSplit;
                    inSplit = this->receiveInputFromClient();
                    if (inSplit == "hit") {
                        if (player->hit(false)) {
                            this->giveCard(*player);
                        }
                        if (player->calculateValueOfHand() > 21) {

                            player->setBust(true, false);
                            cout << "bust " << endl;
                            this->sendMessageToClient("bust \n");
                            koniecNormal = true;
                        } else if (player->calculateValueOfHand() == 21){
                            cout << "win " << endl;
                            this->sendMessageToClient("win \n");
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
                    this->sendMessageToClient("hand 2 \n");
                    this->sendMessageToClient(player->printDeckSplit());
                    cout << "hit/stand " << endl;
                    this->sendMessageToClient("hit/stand ");
                    this->sendMessageToClient(";specialMessageMove");

//                    cin >> inSplit;
                    inSplit = this->receiveInputFromClient();
                    if (inSplit == "hit") {
                        if (player->hit(true)) {
                            this->giveCardSplit(*player);
                        }
                        if (player->calculateValueOfHandSplit() > 21) {

                            player->setBust(true, true);
                            cout << "bust " << endl;
                            this->sendMessageToClient("bust ");
                            koniecSplit = true;
                        } else if (player->calculateValueOfHandSplit() == 21){
                            cout << "win " << endl;
                            this->sendMessageToClient("win ");
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
                this->sendMessageToClient("wrong input ");

            }

            if (!player->getFirstMove()) {
                player->setFirstMove(true);
            }

        }
        this->sendMessageToClient(player->printDeck());

    }

    //posledne ked hraci dovyberaju
    this->sendMessageToClient(this->dealer.printDeck(true));

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
        this->sendMessageToClient("DEALER WINS after split ");
    }


    if (countBust == listOfPlayers.size()) {
        cout << "DEALER WINS" << endl;
        this->sendMessageToClient("DEALER WINS");
    } else {
        while(this->dealer.calculateValueOfHand() < 17) {
            bool dealerWin = true;
            this->sendMessageToClient(this->dealer.printDeck(true));
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
                this->sendMessageToClient("DEALER WINS");
                this->getWinner(dealerWin);
                break;
            }
            this->dealer.hit();

            this->sendMessageToClient(this->dealer.printDeck(true));
        }
    }
    cout << "end of game" << endl;
    this->sendMessageToClient("end of game");

    this->getWinner(false);

    cout << "" << endl;
    cout << "Actuall balance: " << endl;
    this->sendMessageToClient("\n Actuall balance: \n");
    for (auto& player: listOfPlayers) {
        cout << player->getName() << " " << player->getBalance() << endl;
        this->sendMessageToClient(player->getName());
        this->sendMessageToClient("\n");
        this->sendMessageToClient(to_string(player->getBalance()));
    }
    this->sendMessageToClient(";endOfLoop");

}



void House::getWinner(bool dealerWin) {
    cout << "" << endl;
    cout << "--------GAME RECAP---------" << endl;
    this->dealer.printDeck(true);
    this->sendMessageToClient("\n --------GAME RECAP---------");
    this->sendMessageToClient(this->dealer.printDeck(true));
    for (auto& player: listOfPlayers) {
        player->printDeck();
        this->sendMessageToClient(player->printDeck());
        if (player->getIsHandSplit()) {
            player->printDeckSplit();
            this->sendMessageToClient(player->printDeckSplit());
        }
    }

    cout << "" << endl;
    cout << "--------WINNERS---------" << endl;
    this->sendMessageToClient("\n --------WINNERS---------");
    if (!dealerWin) {
        for (auto& player: listOfPlayers) {
            if (player->getIsHandSplit()) {
                cout << "Hand 1: " << endl;
                this->sendMessageToClient("Hand 1: ");
            }
            if (player->calculateValueOfHand() > this->dealer.calculateValueOfHand() && !player->isBust(false)) {
                cout << player->getName() << " " << player->getDeposit() << " x2" << endl;
                cout <<  "Total win: " << (player->getDeposit()*2) << endl;
                this->sendMessageToClient(player->getName());
                this->sendMessageToClient(" ");
                this->sendMessageToClient(to_string(player->getDeposit()));
                this->sendMessageToClient(" x2\n");
                this->sendMessageToClient("Total win: ");
                this->sendMessageToClient(to_string((player->getDeposit()*2)));

                player->updateBalance(player->getDeposit()*2);
                cout <<  "Total balance: " << (player->getBalance()) << endl;
                this->sendMessageToClient("Total balance: ");
                this->sendMessageToClient(to_string(player->getBalance()));


            } else if (player->calculateValueOfHand() == this->dealer.calculateValueOfHand() && !player->isBust(false)) {
                cout << player->getName() << " " << player->getDeposit() << " x1" << endl;
                cout <<  "Total win: " << (player->getDeposit()) << endl;
                player->updateBalance(player->getDeposit());
                cout <<  "Total balance: " << (player->getBalance()) << endl;

                this->sendMessageToClient(player->getName());
                this->sendMessageToClient(" ");
                this->sendMessageToClient(to_string(player->getDeposit()));
                this->sendMessageToClient(" x1\n");
                this->sendMessageToClient("Total win: ");
                this->sendMessageToClient(to_string((player->getDeposit())));

                this->sendMessageToClient("Total balance: ");
                this->sendMessageToClient(to_string(player->getBalance()));


            } else if (this->dealer.calculateValueOfHand() > 21 && !player->isBust(false)) {
                cout << player->getName() << " " << player->getDeposit() << " x2" << endl;
                cout <<  "Total win: " << (player->getDeposit()*2) << endl;
                this->sendMessageToClient(player->getName());
                this->sendMessageToClient(" ");
                this->sendMessageToClient(to_string(player->getDeposit()));
                this->sendMessageToClient(" x2\n");
                this->sendMessageToClient("Total win: ");
                this->sendMessageToClient(to_string((player->getDeposit()*2)));

                player->updateBalance(player->getDeposit()*2);
                cout <<  "Total balance: " << (player->getBalance()) << endl;

                this->sendMessageToClient("Total balance: ");
                this->sendMessageToClient(to_string(player->getBalance()));
            }

            //pre split

            if (player->getIsHandSplit()) {

                if (player->calculateValueOfHandSplit() > this->dealer.calculateValueOfHand() && !player->isBust(true)) {
                    cout << "Hand 2: " << endl;
                    cout << player->getName() << " " << player->getDeposit() << " x2" << endl;
                    cout <<  "Total win: " << (player->getDeposit()*2) << endl;

                    this->sendMessageToClient("Hand 2: ");
                    this->sendMessageToClient(player->getName());
                    this->sendMessageToClient(" ");
                    this->sendMessageToClient(to_string(player->getDeposit()));
                    this->sendMessageToClient(" x2\n");
                    this->sendMessageToClient("Total win: ");
                    this->sendMessageToClient(to_string((player->getDeposit()*2)));

                    player->updateBalance(player->getDeposit()*2);
                    cout <<  "Total balance: " << (player->getBalance()) << endl;

                    this->sendMessageToClient("Total balance: ");
                    this->sendMessageToClient(to_string(player->getBalance()));

                } else if (player->calculateValueOfHandSplit() == this->dealer.calculateValueOfHand() && !player->isBust(true)) {
                    cout << "Hand 2: " << endl;
                    cout << player->getName() << " " << player->getDeposit() << " x1" << endl;
                    cout <<  "Total win: " << (player->getDeposit()) << endl;
                    player->updateBalance(player->getDeposit());
                    cout <<  "Total balance: " << (player->getBalance()) << endl;

                    this->sendMessageToClient("Hand 2: ");
                    this->sendMessageToClient(player->getName());
                    this->sendMessageToClient(" ");
                    this->sendMessageToClient(to_string(player->getDeposit()));
                    this->sendMessageToClient(" x1\n");
                    this->sendMessageToClient("Total win: ");
                    this->sendMessageToClient(to_string((player->getDeposit())));

                    this->sendMessageToClient("Total balance: ");
                    this->sendMessageToClient(to_string(player->getBalance()));

                } else if (this->dealer.calculateValueOfHand() > 21 && !player->isBust(true)) {
                    cout << "Hand 2: " << endl;
                    cout << player->getName() << " " << player->getDeposit() << " x2" << endl;
                    cout <<  "Total win: " << (player->getDeposit()*2) << endl;

                    this->sendMessageToClient("Hand 2: ");
                    this->sendMessageToClient(player->getName());
                    this->sendMessageToClient(" ");
                    this->sendMessageToClient(to_string(player->getDeposit()));
                    this->sendMessageToClient(" x2\n");
                    this->sendMessageToClient("Total win: ");
                    this->sendMessageToClient(to_string((player->getDeposit()*2)));

                    player->updateBalance(player->getDeposit()*2);
                    cout <<  "Total balance: " << (player->getBalance()) << endl;

                    this->sendMessageToClient("Total balance: ");
                    this->sendMessageToClient(to_string(player->getBalance()));

                }
            }
            player->setDeposit(0);

            cout << "" << endl;
            this->sendMessageToClient("\n");
        }
    } else {
        cout << "DEALER WINS" << endl;
        this->sendMessageToClient("DEALER WINS");
    }

    for (auto& player: listOfPlayers) {
        player->removeCards();
    }
    this->dealer.removeCards();
}

void House::getPlayers() {
    cout << "vypis playerov z housu" << endl;
    this->sendMessageToClient("vypis playerov z housu");
    for (auto& player: this->listOfPlayers) {
        cout << player->getName() << " " << player->getBalance()  << endl;
        this->sendMessageToClient(player->getName());
        this->sendMessageToClient(" ");
        this->sendMessageToClient(to_string(player->getBalance()));
    }
}



House::~House() {
    // Close sockets
    close(clientSocket);
    close(serverSocket);
}







