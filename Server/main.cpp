#include "Card.h"
#include "GameDecks.h"
#include "House.h"
#include "Player.h"


using namespace std;

int main() {

    House house;



    auto regina = std::make_unique<Player>("Regina", 1000);
    auto clang = std::make_unique<Player>("Clang", 1000);

    house.pushPlayer(std::move(regina));
    house.pushPlayer(std::move(clang));

    for (int i = 0; i < 2; ++i) {
        house.round();
    }





    return 0;
}
