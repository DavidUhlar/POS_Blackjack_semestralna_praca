
#include "House.h"
int main() {
    // const char* ipAddress = "127.0.0.1";
    const char* ipAddress = "frios2.fri.uniza.sk";
    // int port = 8080;
    int port = 10241;


    Dealer dealer(6);
    ThreadData threadData(&dealer);

    House server;
    server.startListening(ipAddress, port, &threadData);

    return 0;
}
