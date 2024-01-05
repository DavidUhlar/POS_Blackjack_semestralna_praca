
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
