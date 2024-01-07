//
// Created by dadod on 07.01.2024.
//

#include "ThreadData.h"
ThreadData::ThreadData(Dealer* pDealer) : dealer(pDealer) {

}

Dealer* ThreadData::getDealer() {
    return this->dealer;
}

std::mutex& ThreadData::getMutex() {
    return this->mutex;
}