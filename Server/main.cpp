
#include "House.h"
int main() {

//    const char* ipAddress = "127.0.0.1";
    const char* ipAddress = "frios2.fri.uniza.sk";

//    int port = 8080;
    int port = 10241;
    House server;
    server.startListening(ipAddress, port, new ThreadData(new Dealer(6)));




    return 0;
}