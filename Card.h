
#include <string>

#ifndef SEMESTRALKA_CARD_H
#define SEMESTRALKA_CARD_H

using namespace std;

class Card {



    public:
        Card(string symbol, string number, int value);
        string getSymbol();
        string getNumber();
        int getValue();
        ~Card();

    private:
        string symbol;
        string number;
        int value;

};


#endif //SEMESTRALKA_CARD_H
