CC = g++
CFLAGS = -Wall -std=c++11

all:
	$(CC) $(CFLAGS) linkedList.cpp -o bin/linkedList
