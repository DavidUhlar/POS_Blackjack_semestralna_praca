

#include <thread>
#include "House.h"


House::House() {


}

void House::startListening(const char *ipAddress, int port, void* sharedData) {
    ThreadData* threadData = (ThreadData*) sharedData;


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
//        this->clientAddrLen = sizeof(clientAddr);
//        this->clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);

    int connectedClients = 0;
    while(true) {
        while (connectedClients < 2) {
            // Accept connection
            this->clientAddrLen = sizeof(clientAddr);
            int newClientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);

            if (newClientSocket != -1) {
                // Start a new thread to handle the client
    //            std::thread clientThread(&House::round, this, newClientSocket);

                clientSockets.push_back(newClientSocket);
    //            std::thread clientThread(&House::round, this, newClientSocket, std::ref(threadData));
    //            clientThreads.push_back(std::move(clientThread));



            }
            connectedClients++;
            cout << connectedClients << endl;
        }

        if (connectedClients == 2) {
            for (int i = 0; i < 2; ++i) {
                this->sendMessageToClient("zacnitePiectTeraz", clientSockets.at(i));
                threadData->getDealer()->addCard(threadData->getDealer()->handOutCard());

            }


            for (int i = 0; i < 2; ++i) {
                std::thread clientThread(&House::round, this, clientSockets.at(i), std::ref(threadData));
                clientThreads.push_back(std::move(clientThread));
            }
        }

        for (auto& thread : clientThreads) {
            if (thread.joinable()) {
                thread.join();
            }
        }

        threadData->getDealer()->removeCards();
        close(serverSocket);

        for (auto& sock : clientSockets) {
            close(sock);
        }
    }
//    for (int i = 0; i < 2; ++i) {
//        std::thread clientThread(&House::round, this, clientSockets.at(i), std::ref(threadData));
//        clientThread.detach();
//        clientThreads.push_back(std::move(clientThread));
//    }
//

}


void House::sendMessageToClient(const std::string& message, int clientSocket) {
    if (send(clientSocket, message.c_str(), message.size(), 0) == -1) {
        std::cerr << "Failed to send message to client." << std::endl;
    }
}

string House::receiveInputFromClient(int clientSocket) {
    std::string input = "";
    char buffer[1024];

    memset(buffer, 0, sizeof(buffer));

    // Receive data from client
    recv(clientSocket, buffer, sizeof(buffer), 0);
    input += buffer;

    return input;
}

void House::makeDeposit(Player& player, int clientSocket) {
    string in;
    bool koniec = false;
    while (!koniec) {
        cout << " " << endl;
        cout << "Player: " << player.getName() << endl;
        cout << "Select deposit(10/20/100) (balance: " << player.getBalance() << "): " << endl;
        this->sendMessageToClient(" \n", clientSocket);
        this->sendMessageToClient("Player:  ", clientSocket);
        this->sendMessageToClient(player.getName() + "\n", clientSocket);
        this->sendMessageToClient("Select deposit(10/20/100) (balance: " , clientSocket);
        this->sendMessageToClient(to_string(player.getBalance()), clientSocket);
        this->sendMessageToClient("): ", clientSocket);
        this->sendMessageToClient(";specialMessage", clientSocket);
        //        cout << "Leave with: leave " << endl;

        try {
//            cin >> in;

            in = this->receiveInputFromClient(clientSocket);

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
                        this->sendMessageToClient("wrong input ", clientSocket);
                        this->sendMessageToClient("specialMessage", clientSocket);
                    }
                } else {
                    cout << "not enough tokens on account " << endl;
                    this->sendMessageToClient("not enough tokens on account ", clientSocket);
                    this->sendMessageToClient("specialMessage", clientSocket);
                }
            } else {
                cout << "House only accepts 10/20/100 tokens " << endl;
                this->sendMessageToClient("House only accepts 10/20/100 tokens ", clientSocket);
                this->sendMessageToClient("specialMessage", clientSocket);
            }
        } catch (const exception& e) {
            cout << "wrong input " << endl;
            this->sendMessageToClient("wrong input ", clientSocket);

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            this->sendMessageToClient("specialMessage", clientSocket);
        }
    }

}

std::unique_ptr<Player> House::receiveName(int clientSocket) {
    std::string name = "";
    char buffer[1024];

    memset(buffer, 0, sizeof(buffer));

    // Receive data from client
    recv(clientSocket, buffer, sizeof(buffer), 0);
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
//    this->pushPlayer(std::move(regina));

    return regina;

}





void House::giveCard(Player& currentPlayer, void* sharedData) {
    ThreadData* threadData = (ThreadData*) sharedData;
    currentPlayer.addCard(threadData->getDealer()->handOutCard());
}

void House::giveCardSplit(Player& currentPlayer, void* sharedData) {
    ThreadData* threadData = (ThreadData*) sharedData;

    currentPlayer.addCardSplit(threadData->getDealer()->handOutCard());
}

void House::handingOutCards(Player& player, void* sharedData) {
    ThreadData* threadData = (ThreadData*) sharedData;
    for (int i = 0; i < 2; ++i) {


        this->giveCard(player, threadData);

    }

}

//void House::pushPlayer(unique_ptr<Player> player) {
//    this->listOfPlayers.emplace_back(std::move(player));
//}


void House::round(int clientSocket, void* sharedData) {
    ThreadData* threadData = (ThreadData*) sharedData;

//    this->receiveName(clientSocket);
//    Player player;
    std::unique_ptr<Player> player = this->receiveName(clientSocket);
    //cout << "velkost balicka: " << this->dealer.getGameDeckSize() << endl;
    threadData->getDealer()->getGameDeckSize();
    this->makeDeposit(*player, clientSocket);




    int countBustSplitSize = 0;
    int countBustSplit = 0;

    cout << "" << endl;
    cout << "" << endl;
    cout << "----------TABLE-----------" << endl;
    this->sendMessageToClient("\n", clientSocket);
    this->sendMessageToClient("\n", clientSocket);
    this->sendMessageToClient("----------TABLE-----------\n", clientSocket);

    if (threadData->getDealer()->getGameDeckSize() >= 60) {

        this->sendMessageToClient(threadData->getDealer()->printDeck(false), clientSocket);
        cout << threadData->getDealer()->printDeck(false) << endl;


        std::unique_lock<std::mutex> lock(threadData->getMutex());
        this->handingOutCards(*player, threadData);

        threadData->getThreadReady()++;
        threadData->setPlayerCards(player->getName(), player->printDeck());

        if (threadData->getThreadReady() == 2) {
            threadData->getConditionVariable().notify_all();
        }

        threadData->getConditionVariable().wait(lock, [&] { return threadData->getThreadReady() == 2; });

        lock.unlock();





        for (const auto& entry : threadData->getPlayerCards()) {
            const std::string& playerCards = entry.second;

            this->sendMessageToClient(playerCards, clientSocket);
        }

        player->setBust(false, true);
        player->setBust(false, false);
        player->setFirstMove(false);


        this->numberOfRound++;
    } else {
        cout << "je koniec" << endl;
    }

    cout << "" << endl;
    cout << "" << endl;
    cout << "----------GAME-----------" << endl;
    cout << "" << endl;

    this->sendMessageToClient("\n\n ----------GAME-----------\n", clientSocket);

    bool koniec = false;


        cout << "" << endl;
        cout << "Player: " << player->getName() << endl;

        this->sendMessageToClient("\n", clientSocket);
        this->sendMessageToClient("\nPlayer: \n", clientSocket);

        string in;
        string inSplit;
        koniec = false;


        while (!koniec)
        {
            std::unique_lock<std::mutex> lock(threadData->getMutex());

            this->sendMessageToClient( threadData->getDealer()->printDeck(false), clientSocket);
            lock.unlock();
            this->sendMessageToClient( player->printDeck(), clientSocket);

            if (player->calculateValueOfHand() == 21) {
                cout << "BLACKJACK" << endl;
                this->sendMessageToClient("BLACKJACK", clientSocket);
                koniec = true;
                break;
            }


            if (!player->getFirstMove()) {
                if (player->isSplitable()) {
                    cout << "hit/stand/surrender/split/doubleDown " << endl;
                    this->sendMessageToClient( "hit/stand/surrender/split/doubleDown ;", clientSocket);
                    this->sendMessageToClient("specialMessageMove", clientSocket);
                } else {
                    cout << "hit/stand/surrender/doubleDown " << endl;
                    this->sendMessageToClient( "hit/stand/surrender/doubleDown ;", clientSocket);
                    this->sendMessageToClient("specialMessageMove", clientSocket);
                }

            } else {
                cout << "hit/stand " << endl;
                this->sendMessageToClient( "hit/stand ;", clientSocket);
                this->sendMessageToClient("specialMessageMove", clientSocket);
            }

//            cin >> in;
            in = this->receiveInputFromClient(clientSocket);

            if (in == "hit") {
                if (player->hit(false)) {
                    this->giveCard(*player, threadData);
                }
                if (player->calculateValueOfHand() > 21) {

                    player->setBust(true, false);
                    cout << "bust " << endl;
                    this->sendMessageToClient("bust \n", clientSocket);
                    koniec = true;
                } else if (player->calculateValueOfHand() == 21){
                    cout << "win " << endl;
                    this->sendMessageToClient("win \n", clientSocket);
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
                    this->sendMessageToClient("hand 1 \n", clientSocket);
                    this->sendMessageToClient(player->printDeck(), clientSocket);

                    cout << "hit/stand " << endl;
                    this->sendMessageToClient("hit/stand \n", clientSocket);
                    this->sendMessageToClient(";specialMessageMove", clientSocket);


//                    cin >> inSplit;
                    inSplit = this->receiveInputFromClient(clientSocket);
                    if (inSplit == "hit") {
                        if (player->hit(false)) {
                            std::unique_lock<std::mutex> lock(threadData->getMutex());
                            this->giveCard(*player, threadData);
                            lock.unlock();
                        }
                        if (player->calculateValueOfHand() > 21) {

                            player->setBust(true, false);
                            cout << "bust " << endl;
                            this->sendMessageToClient("bust \n", clientSocket);
                            koniecNormal = true;
                        } else if (player->calculateValueOfHand() == 21){
                            cout << "win " << endl;
                            this->sendMessageToClient("win \n", clientSocket);
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
                    this->sendMessageToClient("hand 2 \n", clientSocket);
                    this->sendMessageToClient(player->printDeckSplit(), clientSocket);
                    cout << "hit/stand " << endl;
                    this->sendMessageToClient("\nhit/stand ", clientSocket);
                    this->sendMessageToClient(";specialMessageMove", clientSocket);

//                    cin >> inSplit;
                    inSplit = this->receiveInputFromClient(clientSocket);
                    if (inSplit == "hit") {
                        if (player->hit(true)) {
                            std::unique_lock<std::mutex> lock(threadData->getMutex());
                            this->giveCardSplit(*player, threadData);
                            lock.unlock();
                        }
                        if (player->calculateValueOfHandSplit() > 21) {

                            player->setBust(true, true);
                            cout << "bust " << endl;
                            this->sendMessageToClient("bust \n", clientSocket);
                            koniecSplit = true;
                        } else if (player->calculateValueOfHandSplit() == 21){
                            cout << "win " << endl;
                            this->sendMessageToClient("win \n", clientSocket);
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
                this->sendMessageToClient("wrong input ", clientSocket);

            }

            if (!player->getFirstMove()) {
                player->setFirstMove(true);
            }

        }
        this->sendMessageToClient(player->printDeck(), clientSocket);



    //posledne ked hraci dovyberaju


    this->sendMessageToClient(threadData->getDealer()->printDeck(true), clientSocket);


    int countBust = 0;

    if (player->isBust(false)) {
        countBust++;

    }

    if (player->isBust(true)) {
        countBustSplit++;
    }

    this->sendMessageToClient("end of game \n", clientSocket);

    std::unique_lock<std::mutex> lock(threadData->getMutex());
    threadData->getThreadCounter()++;
    threadData->getConditionVariable().notify_all();
    threadData->getConditionVariable().wait(lock, [&] { return threadData->getThreadCounter() == 2; });
    threadData->getPlayerCards().clear();
    lock.unlock();

    if ((countBustSplit == countBustSplitSize) && (countBustSplitSize > 0)) {
        cout << "DEALER WINS after split " << endl;
        this->sendMessageToClient("DEALER WINS after split ", clientSocket);
    }


    if (countBust == 1) {
        cout << "DEALER WINS" << endl;
        this->sendMessageToClient("DEALER WINS\n", clientSocket);
    } else {

        while(threadData->getDealer()->calculateValueOfHand() < 17) {
            bool dealerWin = true;

            this->sendMessageToClient(threadData->getDealer()->printDeck(true), clientSocket);

                if (threadData->getDealer()->calculateValueOfHand() < player->calculateValueOfHand() && !player->isBust(false)) {
                    dealerWin = false;
                }
                if (player->getIsHandSplit()) {
                    if (threadData->getDealer()->calculateValueOfHand() < player->calculateValueOfHandSplit() && !player->isBust(true)) {
                        dealerWin = false;
                    }
                }


            if (dealerWin) {
                cout << "DEALER WINS" << endl;
                this->sendMessageToClient("DEALER WINS \n", clientSocket);
//                this->getWinner(*player, dealerWin, clientSocket, threadData);
                break;
            }
            std::unique_lock<std::mutex> lock(threadData->getMutex());
            threadData->getDealer()->hit();
            lock.unlock();
            this->sendMessageToClient(threadData->getDealer()->printDeck(true), clientSocket);
        }
    }
    cout << "\nend of game" << endl;
    this->sendMessageToClient("end of game \n", clientSocket);



//    std::unique_lock<std::mutex> lockIt(threadData->getMutex());
//
//    threadData->setReadyTreadyWinner();
//    threadData->getPlayerCards().clear();
//    lockIt.unlock();


    this->getWinner(*player, false, clientSocket, threadData);

    cout << "" << endl;
    cout << "Actuall balance: " << endl;
    string balanceOutput = "\nActuall balance: \n" + player->getName() + ": " + to_string(player->getBalance()) + "\n";
    //this->sendMessageToClient("\nActuall balance: \n", clientSocket);
//
//    cout << player->getName() << " " << player->getBalance() << endl;
//    this->sendMessageToClient(player->getName(), clientSocket);
//    this->sendMessageToClient("\n", clientSocket);
//    this->sendMessageToClient(to_string(player->getBalance()), clientSocket);

    this->sendMessageToClient(balanceOutput, clientSocket);
    this->sendMessageToClient(";endOfLoop", clientSocket);

}



void House::getWinner(Player& player, bool dealerWin, int clientSocket, void* sharedData) {
    ThreadData* threadData = (ThreadData*) sharedData;
    cout << "" << endl;
    cout << "--------GAME RECAP---------" << endl;
    threadData->getDealer()->printDeck(true);
    this->sendMessageToClient("\n --------GAME RECAP--------- \n", clientSocket);


    this->sendMessageToClient(threadData->getDealer()->printDeck(true), clientSocket);


    std::unique_lock<std::mutex> lock(threadData->getMutex());

    threadData->getThreadReadyWinner()++;
    threadData->setPlayerCards(player.getName(), player.printDeck());


    if (threadData->getThreadReadyWinner() == 2) {
        threadData->getConditionVariable().notify_all();
    }

    threadData->getConditionVariable().wait(lock, [&] { return threadData->getThreadReadyWinner() == 2; });

    lock.unlock();



    for (const auto& entry : threadData->getPlayerCards()) {
        const std::string& playerCards = entry.second;
        this->sendMessageToClient(playerCards, clientSocket);
    }


//    player.printDeck();
//    this->sendMessageToClient(player.printDeck(), clientSocket);
    if (player.getIsHandSplit()) {
        player.printDeckSplit();
        this->sendMessageToClient(player.printDeckSplit(), clientSocket);
    }


    cout << "" << endl;
    cout << "--------WINNERS---------" << endl;
    this->sendMessageToClient("\n --------WINNERS--------- \n", clientSocket);
    if (!dealerWin) {

            if (player.getIsHandSplit()) {
                cout << "Hand 1: " << endl;
                this->sendMessageToClient("\nHand 1: ", clientSocket);
            }
            if (player.calculateValueOfHand() > threadData->getDealer()->calculateValueOfHand() && !player.isBust(false)) {
                cout << player.getName() << " " << player.getDeposit() << " x2" << endl;
                cout <<  "Total win: " << (player.getDeposit()*2) << endl;
                string output = player.getName() + " " + to_string(player.getDeposit()) + " x2\n" + "Total win: " + to_string((player.getDeposit()*2)) + "\n";
                this->sendMessageToClient(player.getName(), clientSocket);
                this->sendMessageToClient(" ", clientSocket);
                this->sendMessageToClient(to_string(player.getDeposit()), clientSocket);
                this->sendMessageToClient(" x2\n", clientSocket);
                this->sendMessageToClient("Total win: ", clientSocket);
                this->sendMessageToClient(to_string((player.getDeposit()*2)), clientSocket);
//                this->sendMessageToClient(output, clientSocket);

                cout << output << endl;
                player.updateBalance(player.getDeposit()*2);
//                cout <<  "Total balance: " << (player.getBalance()) << endl;
//                this->sendMessageToClient("Total balance: ", clientSocket);
//                this->sendMessageToClient(to_string(player.getBalance()), clientSocket);


            } else if (player.calculateValueOfHand() == threadData->getDealer()->calculateValueOfHand() && !player.isBust(false)) {
                cout << player.getName() << " " << player.getDeposit() << " x1" << endl;
                cout <<  "Total win: " << (player.getDeposit()) << endl;
                player.updateBalance(player.getDeposit());
                cout <<  "Total balance: " << (player.getBalance()) << endl;

                this->sendMessageToClient(player.getName(), clientSocket);
                this->sendMessageToClient(" ", clientSocket);
                this->sendMessageToClient(to_string(player.getDeposit()), clientSocket);
                this->sendMessageToClient(" x1\n", clientSocket);
                this->sendMessageToClient("Total win: ", clientSocket);
                this->sendMessageToClient(to_string((player.getDeposit())), clientSocket);

                string output = player.getName() + " " + to_string(player.getDeposit()) + " x1\n" + "Total win: " + to_string((player.getDeposit())) + "\n";
//                this->sendMessageToClient(output, clientSocket);
//                this->sendMessageToClient("Total balance: ", clientSocket);
//                this->sendMessageToClient(to_string(player.getBalance()), clientSocket);
                cout << output << endl;

            } else if (threadData->getDealer()->calculateValueOfHand() > 21 && !player.isBust(false)) {
                cout << player.getName() << " " << player.getDeposit() << " x2" << endl;
                cout <<  "Total win: " << (player.getDeposit()*2) << endl;
                this->sendMessageToClient(player.getName(), clientSocket);
                this->sendMessageToClient(" ", clientSocket);
                this->sendMessageToClient(to_string(player.getDeposit()), clientSocket);
                this->sendMessageToClient(" x2\n", clientSocket);
                this->sendMessageToClient("Total win: ", clientSocket);
                this->sendMessageToClient(to_string((player.getDeposit()*2)), clientSocket);


                string output = player.getName() + " " + to_string(player.getDeposit()) + " x2\n" + "Total win: " + to_string((player.getDeposit()*2)) + "\n";
//                this->sendMessageToClient(output, clientSocket);
                cout << output << endl;

                player.updateBalance(player.getDeposit()*2);
                cout <<  "Total balance: " << (player.getBalance()) << endl;

//                this->sendMessageToClient("Total balance: ", clientSocket);
//                this->sendMessageToClient(to_string(player.getBalance()), clientSocket);
            }

            //pre split

            if (player.getIsHandSplit()) {

                if (player.calculateValueOfHandSplit() > threadData->getDealer()->calculateValueOfHand() && !player.isBust(true)) {
                    cout << "Hand 2: " << endl;
                    cout << player.getName() << " " << player.getDeposit() << " x2" << endl;
                    cout <<  "Total win: " << (player.getDeposit()*2) << endl;

                    this->sendMessageToClient("Hand 2: \n", clientSocket);
                    this->sendMessageToClient(player.getName(), clientSocket);
                    this->sendMessageToClient(" ", clientSocket);
                    this->sendMessageToClient(to_string(player.getDeposit()), clientSocket);
                    this->sendMessageToClient(" x2\n", clientSocket);
                    this->sendMessageToClient("Total win: ", clientSocket);
                    this->sendMessageToClient(to_string((player.getDeposit()*2)), clientSocket);

                    player.updateBalance(player.getDeposit()*2);
                    cout <<  "Total balance: " << (player.getBalance()) << endl;

                    string output = player.getName() + " " + to_string(player.getDeposit()) + " x2\n" + "Total win: " + to_string((player.getDeposit()*2)) + "\n";
//                    this->sendMessageToClient(output, clientSocket);
//                    this->sendMessageToClient("Total balance: ", clientSocket);
//                    this->sendMessageToClient(to_string(player.getBalance()), clientSocket);
                    cout << output << endl;

                } else if (player.calculateValueOfHandSplit() == threadData->getDealer()->calculateValueOfHand() && !player.isBust(true)) {
                    cout << "Hand 2: " << endl;
                    cout << player.getName() << " " << player.getDeposit() << " x1" << endl;
                    cout <<  "Total win: " << (player.getDeposit()) << endl;
                    player.updateBalance(player.getDeposit());
                    cout <<  "Total balance: " << (player.getBalance()) << endl;

                    this->sendMessageToClient("Hand 2: \n", clientSocket);
                    this->sendMessageToClient(player.getName(), clientSocket);
                    this->sendMessageToClient(" ", clientSocket);
                    this->sendMessageToClient(to_string(player.getDeposit()), clientSocket);
                    this->sendMessageToClient(" x1\n", clientSocket);
                    this->sendMessageToClient("Total win: ", clientSocket);
                    this->sendMessageToClient(to_string((player.getDeposit())), clientSocket);
//
//                    this->sendMessageToClient("Total balance: ", clientSocket);
//                    this->sendMessageToClient(to_string(player.getBalance()), clientSocket);
                    string output = player.getName() + " " + to_string(player.getDeposit()) + " x1\n" + "Total win: " + to_string((player.getDeposit())) + "\n";
//                    this->sendMessageToClient(output, clientSocket);
                    cout << output << endl;

                } else if (threadData->getDealer()->calculateValueOfHand() > 21 && !player.isBust(true)) {
                    cout << "Hand 2: " << endl;
                    cout << player.getName() << " " << player.getDeposit() << " x2" << endl;
                    cout <<  "Total win: " << (player.getDeposit()*2) << endl;

                    this->sendMessageToClient("Hand 2: ", clientSocket);
                    this->sendMessageToClient(player.getName(), clientSocket);
                    this->sendMessageToClient(" ", clientSocket);
                    this->sendMessageToClient(to_string(player.getDeposit()), clientSocket);
                    this->sendMessageToClient(" x2\n", clientSocket);
                    this->sendMessageToClient("Total win: ", clientSocket);
                    this->sendMessageToClient(to_string((player.getDeposit()*2)), clientSocket);

                    player.updateBalance(player.getDeposit()*2);
                    cout <<  "Total balance: " << (player.getBalance()) << endl;

                    string output = player.getName() + " " + to_string(player.getDeposit()) + " x2\n" + "Total win: " + to_string((player.getDeposit()*2)) + "\n";
//                    this->sendMessageToClient(output, clientSocket);
//                    this->sendMessageToClient("Total balance: ", clientSocket);
//                    this->sendMessageToClient(to_string(player.getBalance()), clientSocket);
                    cout << output << endl;

                }
            }
            player.setDeposit(0);

            cout << "" << endl;
            this->sendMessageToClient("\n", clientSocket);

    } else {
        cout << "DEALER WINS" << endl;
        this->sendMessageToClient("DEALER WINS", clientSocket);
    }


        player.removeCards();

//    std::unique_lock<std::mutex> lock(threadData->getMutex());
//    threadData->getDealer()->removeCards();
//    lock.unlock();
}

//void House::getPlayers() {
//    cout << "vypis playerov z housu" << endl;
//    this->sendMessageToClient("vypis playerov z housu");
//    for (auto& player: this->listOfPlayers) {
//        cout << player->getName() << " " << player->getBalance()  << endl;
//        this->sendMessageToClient(player->getName());
//        this->sendMessageToClient(" ");
//        this->sendMessageToClient(to_string(player->getBalance()));
//    }
//}



House::~House() {
    // Close sockets
//    close(clientSocket);
//    close(serverSocket);
}







