
#include "House.h"
int main() {

//    const char* ipAddress = "127.0.0.1";
    const char* ipAddress = "frios2.fri.uniza.sk";

//    int port = 8080;
    int port = 12069;
    House server;
    server.startListening(ipAddress, port);
//    server.sendMessageToClient("Hello from the server!");

//    server.receiveName();
//    server.getPlayers();
//    server.round();
//    auto regina = std::make_unique<Player>("Regina", 1000);
//    auto clang = std::make_unique<Player>("Clang", 1000);
//    house.pushPlayer(std::move(regina));
//    house.pushPlayer(std::move(clang));




    return 0;
}