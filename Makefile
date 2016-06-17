CC = g++
CFLAGS = -Wall -std=c++11

all:
	$(CC) $(CFLAGS) linkedList.cpp -o bin/linkedList
	$(CC) $(CFLAGS) stack.cpp -o bin/stack
	$(CC) $(CFLAGS) queue.cpp -o bin/queue
	$(CC) $(CFLAGS) trie.cpp -o bin/trie
