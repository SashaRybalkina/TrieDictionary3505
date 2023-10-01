CC = g++
FLAGS = -Wall -fsanitize=undefined -fsanitize=address

TrieTests: Trie.o TrieTests.o
	$(CC) $(FLAGS) -o TrieTest Trie.o TrieTests.o

Trie.o: Trie.h Trie.cpp
	$(CC) $(FLAGS) -c Trie.cpp

TrieTests.o: TrieTests.cpp Trie.h
	$(CC) $(FLAGS) -c TrieTests.cpp

clean:
	rm -f *.o TrieTests
test:
	./TrieTests file1.txt file2.txt