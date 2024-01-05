//
// Created by dadod on 05.01.2024.
//

#ifndef SEMESTRALKA_CLIENT_H
#define SEMESTRALKA_CLIENT_H

#include <iostream>

using namespace std;

class Client {

    public:
        Client();
        string getName();
        void setName();
        ~Client();

    private:
        string name;

};


#endif //SEMESTRALKA_CLIENT_H
