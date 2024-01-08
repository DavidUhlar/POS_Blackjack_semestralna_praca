CC = g++
CFLAGS = -Wall -pthread -std=c++17
LDFLAGS =

.PHONY: all clean client server

all: server client

SERVER_DIR := Server
CLIENT_DIR := Client

SERVER_SRC := $(wildcard $(SERVER_DIR)/*.cpp)
SERVER_HEADERS := $(wildcard $(SERVER_DIR)/*.h)
server: $(SERVER_SRC) $(SERVER_HEADERS)
	$(CC) $(CFLAGS) $(SERVER_SRC) -o serverApp $(LDFLAGS)

CLIENT_SRC := $(wildcard $(CLIENT_DIR)/*.cpp)
CLIENT_HEADERS := $(wildcard $(CLIENT_DIR)/*.h)
client: $(CLIENT_SRC) $(CLIENT_HEADERS)
	$(CC) $(CFLAGS) $(CLIENT_SRC) -o clientApp $(LDFLAGS)

clean:
	rm -f clientApp serverApp $(CLIENT_DIR)/*.o $(SERVER_DIR)/*.o