//
// Created by dadod on 30.12.2023.
//

#ifndef SEMESTRALKA_CARD_H
#define SEMESTRALKA_CARD_H

using namespace std;

class Card {



    public:
        Card(char symbol, char number, int value);
        char getSymbol();
        char getNumber();
        int getValue();
        ~Card();

    private:
        char symbol;
        char number;
        int value;

};


#endif //SEMESTRALKA_CARD_H
