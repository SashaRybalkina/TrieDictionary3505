/*
Name: Sasha Rybalkina
Class: CS3505
Assignment: A5: Refactoring and Testing
Date: October 3, 2023
*/

#ifndef TRIE_H
#define TRIE_H
#include <iostream>
#include <string>
#include <vector>
#include <map>

/// @brief The Trie class creates a tree with a potential to have 26
/// branches of Tries. Each branch represents an implied character,
/// with the branches being created whenever a new word gets added to
/// the trie. The Trie class gives you the option to check if it
/// contains a specific word, and can also return a list of words that
/// it contains that start with a specific prefix.

class Trie
{
    private:
        std::map<char, Trie> branching;
        bool isAWord;
        void checkAllBranches(std::vector<std::string> &words, std::string buildString);
        bool checkIfValid(std::string word);
        void traverseAndAdd(char first, std::string subString);
        void getAllWordsOfPrefix(std::vector<std::string> &allWords, std::string prefix);

    public:
        Trie();
        ~Trie();
        Trie(Trie &other);
        Trie& operator=(Trie other);
        void addWord(std::string s);
        bool isWord(std::string s);
        std::vector<std::string> allWordsStartingWithPrefix(std::string s);    
};
#endif