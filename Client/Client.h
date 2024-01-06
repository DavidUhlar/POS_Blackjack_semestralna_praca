

#ifndef SEMESTRALKA_CLIENT_H
#define SEMESTRALKA_CLIENT_H

#include <iostream>

using namespace std;

class Client {
    public:
        Client();
        string getName();
        void setName();
        void setDeposit();
        void setMove();
        string getDeposit();
        string getMove();
        ~Client();

    private:
        string name;
        string deposit;
        string move;

};


#endif //SEMESTRALKA_CLIENT_H
