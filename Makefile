CC=g++
CFLAGS=-std=c++11 -pthread -g
LDFLAGS=
SRC_DIR=./src
SOURCES=./src/main.cpp ./src/CGraph.cpp
OBJECTS=$(SOURCES:.cpp=.o)
BIN_DIR=./bin
EXECUTABLE=main.o

all:
	test -d $(BIN_DIR) || mkdir $(BIN_DIR)
	$(CC) $(CFLAGS) $(SOURCES) -o $(BIN_DIR)/$(EXECUTABLE)	

clean:
	rm -rf $(BIN_DIR)/*.o
