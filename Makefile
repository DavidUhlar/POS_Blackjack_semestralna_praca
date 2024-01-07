CC = g++
CFLAGS = -Wall -pthread -std=c++11

.PHONY: all clean client server

all: server client


SERVER_CPP = server/Card.cpp server/Dealer.cpp server/gameDecks.cpp server/House.cpp server/main.cpp server/Player.cpp server/ThreadData.cpp
SERVER_HEADERS = $(wildcard server/*.h)
server: $(SERVER_CPP) $(SERVER_HEADERS)
	$(CC) $(CFLAGS) $(SERVER_CPP) -o serverApp

CLIENT_CPP = client/Client.cpp client/main_client.cpp client/my_socket.cpp
CLIENT_HEADERS = $(wildcard client/*.h)
client: $(CLIENT_CPP) $(CLIENT_HEADERS)
	$(CC) $(CFLAGS) $(CLIENT_CPP) -o clientApp

clean:
	rm -f clientApp serverApp client/*.o server/*.o
