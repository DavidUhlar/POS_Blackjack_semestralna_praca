cmake_minimum_required(VERSION 3.18)
project(semestralka)

set(CMAKE_CXX_STANDARD 17)

add_executable(semestralka main.cpp
        Card.cpp
        GameDecks.cpp
        Card.h
        GameDecks.h
        Player.cpp
        Player.h
        Dealer.cpp
        Dealer.h
        House.cpp
        House.h)

