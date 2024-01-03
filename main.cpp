#include "Card.h"
#include "GameDecks.h"
#include "House.h"
#include "Player.h"


using namespace std;

int main() {

    House house;



    house.pushPlayer(Player("Regina", 100));
    house.pushPlayer(Player("Clang", 20));
    house.round();




    return 0;
}
