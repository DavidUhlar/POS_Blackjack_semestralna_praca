#include "Card.h"
#include "GameDecks.h"
#include "House.h"
#include "Player.h"


using namespace std;

int main() {

    House house;



    house.pushPlayer(Player("Regina", 1000));
    house.pushPlayer(Player("Clang", 1000));
    for (int i = 0; i < 2; ++i) {
        house.round();
    }





    return 0;
}
