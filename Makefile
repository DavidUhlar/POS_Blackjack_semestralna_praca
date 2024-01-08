CC = g++
CFLAGS = -Wall -pthread -std=c++11

.PHONY: all clean client server

all: server client


SERVER_CPP = Server/Card.cpp Server/Dealer.cpp Server/gameDecks.cpp Server/House.cpp Server/main.cpp Server/Player.cpp Server/ThreadData.cpp
SERVER_HEADERS = $(wildcard Server/*.h)
server: $(SERVER_CPP) $(SERVER_HEADERS)
	$(CC) $(CFLAGS) $(SERVER_CPP) -o serverApp

CLIENT_CPP = Client/Client.cpp Client/main_client.cpp Client/my_socket.cpp
CLIENT_HEADERS = $(wildcard Client/*.h)
client: $(CLIENT_CPP) $(CLIENT_HEADERS)
	$(CC) $(CFLAGS) $(CLIENT_CPP) -o clientApp

clean:
	rm -f clientApp serverApp Client/*.o Server/*.o

