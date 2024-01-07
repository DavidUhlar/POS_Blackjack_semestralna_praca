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
        std::condition_variable& getConditionVariableNotification();
        int& getThreadCounter();
        int& getThreadReady();
        std::unordered_map<std::string, std::string>& getPlayerCards();
        void setPlayerCards(string playerName, const std::string& playerCards);
        void setNotificationReady(bool value);
        bool& getNotificationReady();


    private:
        Dealer* dealer;
        std::mutex mutex;
        std::condition_variable waitCondVariable;
        std::condition_variable notificationCV;
        int threadCounter=0;
        int readyThreads=0;
        std::unordered_map<string, std::string> playerCardsMap;
        bool notificationReady;

};


#endif //SEMESTRALKA_THREADDATA_H
