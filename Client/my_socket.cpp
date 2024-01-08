#include "my_socket.h"
#include <stdexcept>
#include <cstring>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

#define SOCKET_TERMINATE_CHAR '\0'

const char* MySocket::endMessage = ":end";  // modify as needed

MySocket* MySocket::createConnection(std::string hostName, short port) {
    struct addrinfo hints, *result = NULL;
    int iResult;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;


    iResult = getaddrinfo(hostName.c_str(), std::to_string(port).c_str(), &hints, &result);
    if (iResult != 0) {
        throw std::runtime_error("getaddrinfo failed with error: " + std::to_string(iResult) + "\n");
    }


    int connectSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (connectSocket == -1) {
        freeaddrinfo(result);
        throw std::runtime_error("socket failed\n");
    }

    // Connect
    iResult = connect(connectSocket, result->ai_addr, result->ai_addrlen);
    freeaddrinfo(result);
    if (iResult == -1) {
        close(connectSocket);
        throw std::runtime_error("Unable to connect to server\n");
    }

    return new MySocket(connectSocket);
}

MySocket::MySocket(int socket) :
        connectSocket(socket) {

}

MySocket::~MySocket() {
    if (this->connectSocket != -1) {
        close(this->connectSocket);
        this->connectSocket = -1;
    }
}


void MySocket::sendData(const std::string &data) {
    size_t data_length = data.length();
    char* buffer = (char*)calloc(data_length + 1, sizeof(char));
    memcpy(buffer, data.c_str(), data_length);
    buffer[data_length] = SOCKET_TERMINATE_CHAR;

    int iResult = send(connectSocket, buffer, data_length + 1, 0);
    free(buffer);
    if (iResult == -1) {
        throw std::runtime_error("send failed\n");
    }
}

void MySocket::sendEndMessage() {
    this->sendData(this->endMessage);
}

std::string MySocket::receiveData() {
    char buffer[1024];

    memset(buffer, 0, sizeof(buffer));

    ssize_t bytesReceived = recv(this->connectSocket, buffer, sizeof(buffer), 0);

    if (bytesReceived == -1) {
        throw std::runtime_error("receive failed\n");
    } else if (bytesReceived == 0) {
        throw std::runtime_error("Connection closed\n");
    } else {
        return std::string(buffer, bytesReceived);
    }
}

std::string MySocket::serialize(std::string &output, std::string &meno, int balance) {
    output += meno + ";" + std::to_string(balance) + ";";
    return output;
}
#undef SOCKET_TERMINATE_CHAR
