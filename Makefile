TARGET = sntanks
SRC_DIR = src/
INC_DIR = include/
LIBS = `sdl-config --libs`
CFLAGS = `sdl-config --cflags`
CC = g++

all:
	$(CC) $(CFLAGS) -c $(SRC_DIR)videoCore.cpp -o videoCore.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)gameCore.cpp -o gameCore.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)sntanks.cpp -o sntanks.o
	$(CC) -o $(TARGET) videoCore.o gameCore.o sntanks.o $(LIBS)
clean:
	rm -rf *.o $(TARGET)
