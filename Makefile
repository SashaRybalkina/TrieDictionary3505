CC = g++ -std=c++2a
GOOGLETEST = ./googletest
LIBRARY = -L$(GOOGLETEST)/lib
INCLUDE = -I$(GOOGLETEST)/googletest/include
FLAGS = -Wall -fsanitize=undefined -fsanitize=address

TrieTests: Trie.o TrieTests.o
	$(CC) $(INCLUDE) -o TrieTests Trie.cpp  TrieTests.cpp $(LIBRARY) -lgtest

Trie.o: Trie.h Trie.cpp
	$(CC) -c Trie.cpp

TrieTests.o: TrieTests.cpp Trie.h
	$(CC) $(INCLUDE) -c TrieTests.cpp

clean:
	rm -f *.o TrieTests
test:
	./TrieTests