
#include "Player.h"
#include "Dealer.h"
#include <memory>
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sstream>

#ifndef SEMESTRALKA_HOUSE_H
#define SEMESTRALKA_HOUSE_H

using namespace std;

class House {
public:
    House(const char *ipAddress, int port);
    void makeDeposit(Player& player);
    void receiveName();
    void sendMessageToClient(const std::string& message);
    void giveCard(Player& player);
    void giveCardSplit(Player& player);
    void handingOutCards();
    void round();
    void pushPlayer(unique_ptr<Player> player);
    void getWinner(bool dealerWin);
    void getPlayers();
    string receiveInputFromClient();
    ~House();
private:
    Dealer dealer;
    vector<unique_ptr<Player>> listOfPlayers;
    int numberOfRound;
    int serverSocket;
    int clientSocket;
    struct sockaddr_in serverAddr;
    struct sockaddr_in clientAddr;
    socklen_t clientAddrLen;
};

#endif //SEMESTRALKA_HOUSE_H
