/*
Name: Sasha Rybalkina
Class: CS3505
Assignment: A5: Refactoring and Testing
Date: October 3, 2023
*/

#include <iostream>
#include <string>
#include <vector>
#include "Trie.h"
#include <map>
using std::string;
using std::vector;
using std::map;

/// @brief The Trie class creates a tree with a potential to have 26
/// branches of Tries. Each branch represents an implied character,
/// with the branches being created whenever a new word gets added to
/// the trie. The Trie class gives you the option to check if it
/// contains a specific word, and can also return a list of words that
/// it contains that start with a specific prefix.

/// Constructor.
Trie::Trie()
{
    isAWord = false;
}

/// Deconstructor. Deletes every branch that Trie has.
Trie::~Trie()
{
    for (int i = 0; i < 26; i++)
    {
        char currentChar = i + 'a';
        if (branching.count(currentChar))
        {
            branching.erase(currentChar);
        }
    }
}

/// Copy constructor. Copies every branch of the other Trie into
/// the current Trie.
Trie::Trie(Trie &other)
{
    isAWord = other.isAWord;
    for (int i = 0; i < 26; i++)
    {
        char currentChar = i + 'a';
        if (other.branching.count(currentChar))
        {
            branching[currentChar] = other.branching[currentChar];
        }
    }
}

/// Overloaded '=' operator. Swaps the pointers and primitives of
/// this Trie and the other Trie.
Trie &Trie::operator=(Trie other)
{
    std::swap(branching, other.branching);
    std::swap(this->isAWord, other.isAWord);
    return *this;
}

/// @brief Private helper method for recursively checking every
/// branch of a branch for a word and then returning a vector of
/// all the words found. Used in allWordsStartingWithPrefix.
void Trie::checkAllBranches(vector<string> &words, string buildString)
{
    for (int i = 0; i < 26; i++)
    {
        string copy = buildString;
        char currentChar = i + 'a';
        /// If branch exists, check its branches and check if it's
        /// an ending of an existing word.
        if (branching.count(currentChar))
        {
            copy += (currentChar);
            if (branching[currentChar].isAWord)
            {
                words.push_back(copy);
            }
            branching[currentChar].checkAllBranches(words, copy); 
        }
    }
}

/// @brief Private helper method for checking if a string is a-z.
/// @param word: The word being checked.
/// @return True if the string is a valid word. False otherwise.
bool Trie::checkIfValid(string word)
{
    for (int i = 0; i < word.size(); i++)
    {
        if (!(isalpha(word[i]) && word[i] >= 'a'))
        {
            return false;
        }
    }
    return true;
}

/// @brief Takes in a word and adds it to the trie by recursively
/// adding each character of the word as a branch in the branches
/// array. Once the word is added, the isAWord flag of the last
/// character of the word gets set to true.
/// @param word: The word being added to the trie.
void Trie::addWord(string word)
{
    if (word.size() != 0)
    {
        char first = word[0];
        string newString = word.substr(1);
        /// If this branch already exists, we do not want to replace
        /// it with a new one, and so we skip it.
        if (branching.count(first))
        {
            branching[first].addWord(newString);
        }
        else
        {
            Trie temp;
            temp.addWord(newString);
            /// Set this branch in the current Trie to the new branch we
            /// created.
            branching[first] = temp;
        }
    }
    else
    {
        isAWord = true;
    }
}

/// @brief Checks if the word is in the trie by recursively traversing
/// through the trie until the last character of the word and returning
/// the isAWord flag of that character.
/// @param word: The word being searched for in the trie.
/// @return True if this word is in the trie, false otherwise.
bool Trie::isWord(string word)
{
    /// Checks if the word is valid. If not, returns false.
    if (!checkIfValid(word))
    {
        return false;
    }
    char firstChar = word[0];

    /// If the last character of word is reached, check if it is
    /// a word in the Trie
    if (word.size() == 0)
    {
        return isAWord;
    }
    /// Traverse down to the last character of the word if the
    /// current node is not null.
    else if (branching.count(firstChar))
    {
        string newString = word.substr(1);
        return branching[firstChar].isWord(newString);
    }
    return false;
}

/// @brief Recursively finds every word in the trie that starts with
/// the given prefix.
/// @param prefix: The prefix of all the words returned.
/// @return A string vector containg all the words in the trie that
/// start with the prefix.
vector<string> Trie::allWordsStartingWithPrefix(string prefix)
{
    vector<string> allWords;
    
    /// Checks if the prefix is valid. If not, returns an empty vector.
    if (!checkIfValid(prefix))
    {
        return allWords;
    }
    /// If the prefix is a word, it should be added to the vector.
    if (isWord(prefix))
    {
        allWords.push_back(prefix);
    }
    
    /// Traverses down to the last character of the prefix and calls
    /// the checkAllBranches method on the node of the last character
    /// once it is reached.
    if (branching.count(prefix[0]))
    {
        Trie temp = branching[prefix[0]];
        if (prefix.size() == 1)
        {
            temp.checkAllBranches(allWords, prefix);
        }
        else
        {
            for (int i = 1; i < prefix.size(); i++)
            {
                char current = prefix[i];
                temp = temp.branching[current];
                if (i == prefix.size() - 1 && temp.branching.count(current))
                {
                    temp.checkAllBranches(allWords, prefix);
                }
            }
        }
    }
    else
    {
        checkAllBranches(allWords, prefix);
    }
    return allWords;
}