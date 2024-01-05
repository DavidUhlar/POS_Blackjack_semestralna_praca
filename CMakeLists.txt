cmake_minimum_required(VERSION 3.18)
project(semestralka)

set(CMAKE_CXX_STANDARD 17)

add_executable(semestralka_server Server/main.cpp
        Server/Card.cpp
        Server/GameDecks.cpp
        Server/Card.h
        Server/GameDecks.h
        Server/Player.cpp
        Server/Player.h
        Server/Dealer.cpp
        Server/Dealer.h
        Server/House.cpp
        Server/House.h
        Server/Server.cpp
        Server/Server.h
)
        
add_executable(semestralka_client Client/main_client.cpp
        Client/Client.cpp
        Client/Client.h
        Client/my_socket.cpp
        Client/my_socket.h
)

target_link_libraries(semestralka_server pthread)
