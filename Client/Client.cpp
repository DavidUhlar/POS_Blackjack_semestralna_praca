
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
    string in;
    cout << "Input deposit" << endl;
    cin >> in;
    this->deposit = in;
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





