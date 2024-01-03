#include "Card.h"
#include "GameDecks.h"
#include "House.h"
#include "Player.h"


using namespace std;

int main() {
    House house;

    // Create a Player and add to the House
    unique_ptr<Player> player = make_unique<Player>();
    house.pushPlayer(std::move(player));

    house.round();

    return 0;
}
