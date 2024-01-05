
#include <iostream>
#include "Client.h"
#include "my_socket.h"

using namespace std;



int main() {
    cout << "klient" << endl;

    MySocket* mySocket = MySocket::createConnection("127.0.0.1", 8080);

    Client client;

    client.setName();

    string output;
    string name = client.getName();

    mySocket->sendData(mySocket->serialize(output, name, 1000));

    delete mySocket;
    mySocket = nullptr;
    return 0;



}