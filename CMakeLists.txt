cmake_minimum_required(VERSION 3.18)
project(semestralka)

set(CMAKE_CXX_STANDARD 17)

add_executable(semestralka_server main.cpp
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
        
add_executable(semestralka_client main_client.cpp
        Client.cpp
        Client.h
)

target_link_libraries(semestralka_server pthread)
