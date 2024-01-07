//
// Created by dadod on 07.01.2024.
//

#ifndef SEMESTRALKA_THREADDATA_H
#define SEMESTRALKA_THREADDATA_H
#include "Dealer.h"
#include <mutex>

class ThreadData {

    public:
        ThreadData(Dealer* dealer);
        Dealer* getDealer();
        std::mutex& getMutex();
    private:
        Dealer* dealer;
        std::mutex mutex;
};


#endif //SEMESTRALKA_THREADDATA_H
