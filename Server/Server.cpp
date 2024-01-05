#include "Server.h"

using namespace std;


Server::Server(const char *ipAddress, int port) {
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



void Server::receiveName() {
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
    this->house.pushPlayer(std::move(regina));

}



Server::~Server() {
    // Close sockets
    close(clientSocket);
    close(serverSocket);
}


