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


std::condition_variable& ThreadData::getConditionVariable() {
    return this->waitCondVariable;
}


int& ThreadData::getThreadCounter() {
    return threadCounter;
}

int& ThreadData::getThreadReady() {
    return readyThreads;
}

int& ThreadData::getThreadReadyWinner() {
    return winnerReadyTready;
}

std::unordered_map<string, std::string>& ThreadData::getPlayerCards() {
    return playerCardsMap;
}

void ThreadData::setPlayerCards(string playerName, const std::string& playerCards) {
    playerCardsMap[playerName] = playerCards;
}

void ThreadData::setReadyTready() {
    readyThreads = 0;
}

void ThreadData::setReadyTreadyWinner() {
    winnerReadyTready = 0;
}