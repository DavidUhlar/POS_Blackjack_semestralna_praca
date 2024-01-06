
#ifndef SEMESTRALKA_MY_SOCKET_H
#define SEMESTRALKA_MY_SOCKET_H


#include <iostream>
#include <string>

class MySocket {
public:
    static MySocket* createConnection(std::string hostName, short port);
    ~MySocket();
    void sendData(const std::string& data);
    void sendEndMessage();
    std::string receiveData();
    std::string serialize(std::string &output, std::string &meno, int balance);
protected:
    MySocket(int socket); // Update the constructor declaration
private:
    static const char * endMessage;
    int connectSocket; // Change SOCKET to int for Linux compatibility
};

#endif //SEMESTRALKA_MY_SOCKET_H
