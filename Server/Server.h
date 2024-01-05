
#ifndef SEMESTRALKA_SERVER_H
#define SEMESTRALKA_SERVER_H

#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sstream>
#include "Player.h"
#include "House.h"

using namespace std;



class Server {
    public:
    Server(const char* ipAddress, int port);
    void receiveName();
    ~Server();
    House house;
    private:
        int serverSocket;
        int clientSocket;
        struct sockaddr_in serverAddr;
        struct sockaddr_in clientAddr;
        socklen_t clientAddrLen;

};


#endif //SEMESTRALKA_SERVER_H
