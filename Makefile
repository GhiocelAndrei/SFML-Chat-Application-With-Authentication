CC = g++
CFLAGS = -std=c++11 -Wall
LIBS = -lsfml-network -lsfml-system

CLIENT_SRC_DIR = Client
CLIENT_SRC = $(wildcard $(CLIENT_SRC_DIR)/*.cpp)
CLIENT_OBJ = $(CLIENT_SRC:.cpp=.o)

SERVER_SRC_DIR = Server
SERVER_SRC = $(wildcard $(SERVER_SRC_DIR)/*.cpp)
SERVER_OBJ = $(SERVER_SRC:.cpp=.o)

all: client server

client: $(CLIENT_OBJ)
	$(CC) $(CFLAGS) -o client $(CLIENT_OBJ) $(LIBS)

server: $(SERVER_OBJ)
	$(CC) $(CFLAGS) -o server $(SERVER_OBJ) $(LIBS)

$(CLIENT_OBJ): %.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(SERVER_OBJ): %.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f client server $(CLIENT_OBJ) $(SERVER_OBJ)
