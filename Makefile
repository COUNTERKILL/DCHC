CC=g++
CFLAGS=-std=c++11 -pthread
LDFLAGS=
SRC_DIR=./src
SOURCES=main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
BIN_DIR=./bin
EXECUTABLE=main.o

all:
	test -d $(BIN_DIR) || mkdir $(BIN_DIR)
	$(CC) $(CFLAGS) $(SRC_DIR)/$(SOURCES) -o $(BIN_DIR)/$(EXECUTABLE)	

clean:
	rm -rf $(BIN_DIR)/*.o
