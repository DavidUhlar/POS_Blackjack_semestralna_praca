//
// Created by dadod on 07.01.2024.
//

#ifndef SEMESTRALKA_THREADDATA_H
#define SEMESTRALKA_THREADDATA_H
#include "Dealer.h"
#include <mutex>
#include <condition_variable>

class ThreadData {

    public:
        ThreadData(Dealer* dealer);
        Dealer* getDealer();
        std::mutex& getMutex();
        std::condition_variable& getConditionVariable();
        int& getThreadCounter();
        int& getThreadReady();
        int& getThreadReadyWinner();
        void setReadyTready();
        void setReadyTreadyWinner();
        std::unordered_map<std::string, std::string>& getPlayerCards();
        void setPlayerCards(string playerName, const std::string& playerCards);
        std::unordered_map<std::string, std::string>& getWinners();
        void setWinners(string playerName, const std::string& amount);


    private:
        Dealer* dealer;
        std::mutex mutex;
        std::condition_variable waitCondVariable;
        int threadCounter=0;
        int readyThreads=0;
        int winnerReadyTready=0;
        std::unordered_map<string, std::string> playerCardsMap;
        std::unordered_map<string, std::string> winnersMap;


};


#endif //SEMESTRALKA_THREADDATA_H
