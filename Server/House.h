
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
#include <thread>
#include <vector>
#include <mutex>

#ifndef SEMESTRALKA_HOUSE_H
#define SEMESTRALKA_HOUSE_H

using namespace std;
#include "ThreadData.h"
class House {
public:
    House();
    void startListening(const char *ipAddress, int port, void* sharedData);
    void handleClient(int clientSocket);
    void makeDeposit(Player& player, int clientSocket);
    std::unique_ptr<Player> receiveName(int clientSocket);
    void sendMessageToClient(const std::string& message, int clientSocket);
    void giveCard(Player& player, void* sharedData);
    void giveCardSplit(Player& player, void* sharedData);
    void handingOutCards(Player& player, void* sharedData);
    void round(int clientSocket, void* sharedData);
//    void pushPlayer(unique_ptr<Player> player);
    void getWinner(Player& player, bool dealerWin, int clientSocket, void* sharedData);
//    void getPlayers();
    string receiveInputFromClient(int clientSocket);
    ~House();
private:
//    Dealer dealer;
//    vector<unique_ptr<Player>> listOfPlayers;
    int numberOfRound;
    int serverSocket;
//    int clientSocket;
    struct sockaddr_in serverAddr;
    struct sockaddr_in clientAddr;
    socklen_t clientAddrLen;
    std::vector<std::thread> clientThreads;
    std::vector<int> clientSockets;
    std::mutex mutex;
};

#endif //SEMESTRALKA_HOUSE_H
