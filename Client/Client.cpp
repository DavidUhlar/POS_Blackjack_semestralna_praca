//
// Created by dadod on 05.01.2024.
//

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

Client::~Client() {

}
