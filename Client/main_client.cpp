
#include <iostream>
#include <sstream>
#include "Client.h"
#include "my_socket.h"

using namespace std;



int main() {
    cout << "klient" << endl;

//    MySocket* mySocket = MySocket::createConnection("127.0.0.1", 8080);
    MySocket* mySocket = MySocket::createConnection("frios2.fri.uniza.sk", 10242);

    Client client;


    string message = "";
    cout << message << endl;
    bool end = true;

    while(end) {



//        for (char c : message) {
//            std::cout << "'" << c << "' ASCII: " << static_cast<int>(c) << std::endl;
//        }
//
//        std::cout << "Message from server: [" << message << "], length: " << message.length() << std::endl;

        message = mySocket->receiveData();
        cout << message << endl;
        std::stringstream ss(message);
        std::string token;

        if (message == "zacnitePiectTeraz") {
            client.setName();

            string output;
            string name = client.getName();

            mySocket->sendData(mySocket->serialize(output, name, 1000));
        }
        // Process tokens directly without storing in a vector
        while (std::getline(ss, token, ';')) {
            // Check if the current token is "specialMessage"
            if (token == "specialMessage") {
                client.setDeposit();
                mySocket->sendData(client.getDeposit());
            } else if(token == "specialMessageMove") {
                client.setMove();
                mySocket->sendData(client.getMove());
            } else if (token == "endOfLoop") {
                end = false;
            }

        }


    }


    delete mySocket;
    mySocket = nullptr;
    return 0;



}