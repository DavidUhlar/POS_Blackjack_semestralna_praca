
#include "Client.h"


Client::Client() {

}

string Client::getName() {
    return this->name;
}

void Client::setName() {
    string in;
    cout << "Input name" << endl;
    cin >> in;
    this->name = in;
}

void Client::setDeposit() {
    bool koniec = true;
    while (koniec) {
        string in;
        cout << "Input deposit" << endl;

        try {
            cin >> in;
            int depositLocal = stoi(in);

            if (depositLocal == 10 || depositLocal == 20 || depositLocal == 100) {
                koniec = false;
                this->deposit = to_string(depositLocal);
            }


        } catch (const exception& e) {
            cout << "wrong input " << endl;

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

        }
    }
}

void Client::setMove() {
    string in;
    cout << "Input move" << endl;
    cin >> in;
    this->move = in;
}

string Client::getDeposit() {
    return this->deposit;
}

string Client::getMove() {
    return this->move;
}

Client::~Client() {

}





