TARGET = sntanks
SRC_DIR = src/
INC_DIR = include/
LIBS = `sdl-config --libs`
CFLAGS = -g `sdl-config --cflags`
CC = g++

all:
	$(CC) $(CFLAGS) -c $(SRC_DIR)videoCore.cpp -o videoCore.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)gameCore.cpp -o gameCore.o
	
	$(CC) $(CFLAGS) -c $(SRC_DIR)playerObj.cpp -o playerObj.o
	
	$(CC) $(CFLAGS) -c $(SRC_DIR)coreNetwork.cpp -o coreNetwork.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)net_client.cpp -o net_client.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)net_server.cpp -o net_server.o
	
	$(CC) $(CFLAGS) -c $(SRC_DIR)sntanks.cpp -o sntanks.o
	$(CC) -o $(TARGET) videoCore.o gameCore.o playerObj.o coreNetwork.o net_client.o net_server.o sntanks.o $(LIBS)
clean:
	rm -rf *.o $(TARGET)
