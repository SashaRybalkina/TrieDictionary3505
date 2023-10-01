/*
Name: Sasha Rybalkina
Class: CS3505
Assignment: A4: A Trie and Rule-of-Three
Date: September 26, 2023
*/

#include <fstream>
#include <iostream>
#include <string.h>
#include <vector>
#include "Trie.h"
using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::vector;

/// @brief This tests the addWord, isWord, and allWordsStartingWithPrefix
/// methods of the Trie class as well as the copy constructor and assignment
/// operator.

int main (int argc, char **argv)
{
    ifstream file1(argv[1]);
    ifstream file2(argv[2]);
    Trie trie;

    ///Adds every word from the first file to the trie.
    if (file1.is_open())
    {     
        while (file1)
        {
            string currString; 
            file1 >> currString;
            trie.addWord(currString);
        }       
    }

    // Tests the trie with every prefix from the second file.
    if (file2.is_open())
    {     
        while (file2)
        {
            string currString;
            file2 >> currString;

            /// Sets up the vector containing all the words that start
            /// with the current prefix for the third print statement.
            vector<string> allWords = trie.allWordsStartingWithPrefix(currString);
            string allWordsString = "";
            for (int i = 0; i < allWords.size(); i++)
            {
                allWordsString += allWords[i] + " ";
            }

            /// Prints all testing statements.
            cout << "Checking " << currString << endl;
            if (trie.isWord(currString))
            {
                cout << "Word found" << endl;
            }
            else
            {
                cout << "Word not found" << endl;
            }
            cout << allWordsString << endl;
        }       
    }

    ///This code is responsible for testing Rule-of-Three.
    Trie trieToCopy;
    trieToCopy.addWord("cat");
    Trie trieCopy = trieToCopy;
    cout << trieToCopy.isWord("cat") << endl;
    cout << trieCopy.isWord("cat") << endl;

    Trie trieAssignment;
    trieAssignment = trieToCopy;
    cout << trieToCopy.isWord("cat") << endl;
    cout << trieAssignment.isWord("cat") << endl;
}