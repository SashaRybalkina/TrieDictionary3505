/*
Name: Sasha Rybalkina
Class: CS3505
Assignment: A5: Refactoring and Testing
Date: October 3, 2023
*/
#include <iostream>
#include <string.h>
#include <vector>
#include "Trie.h"
#include <gtest/gtest.h>
using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::vector;

/// @brief This tests the addWord and isWord methods. The testing covers words that
/// share prefixes, words that don't exist in the tree, and empty words.
TEST(TrieTest1, CheckAddWordAndIsWord)
{
    Trie trie;
    trie.addWord("cat");
    trie.addWord("catastrophe");
    trie.addWord("chill");
    trie.addWord("dog");
    trie.addWord("dilled");

    ASSERT_EQ(trie.isWord("cat"), 1) << "Error: Trie does not recognize word when it should.";
    ASSERT_EQ(trie.isWord("catastrophe"), 1) << "Error: Trie does not recognize word when it should.";
    ASSERT_EQ(trie.isWord("daisy"), 0) << "Error: Trie falsely recognizes word.";
    ASSERT_EQ(trie.isWord(""), 0) << "Error: Empty string edge case failed.";
}

/// @brief This tests the allWordsStartingWithPrefix method by generating several
/// vectors with different inputs and then checking their sizes. The inputs are
/// single-character prefixes, prefixes that are words, empty prefixes, invalid
/// prefixes, and capital-case prefixes.
TEST(TrieTest2, CheckAllWordsStartingWithPrefix)
{
    Trie trie;
    trie.addWord("cat");
    trie.addWord("catastrophe");
    trie.addWord("chill");
    trie.addWord("dog");
    trie.addWord("dilled");

    vector<string> wordsWithPrefixC = trie.allWordsStartingWithPrefix("c");
    vector<string> wordsWithPrefixD = trie.allWordsStartingWithPrefix("d");
    vector<string> wordsWithPrefixCat = trie.allWordsStartingWithPrefix("cat");
    vector<string> wordsWithEmptyPrefix = trie.allWordsStartingWithPrefix("");
    vector<string> wordsWithInvalidPrefix = trie.allWordsStartingWithPrefix("ab34");
    vector<string> wordsWithUpperPrefix = trie.allWordsStartingWithPrefix("CAT");

    ASSERT_EQ(wordsWithPrefixCat.size(), 2) << "Error: Vector has incorrect size.";
    ASSERT_EQ(wordsWithPrefixD.size(), wordsWithPrefixCat.size()) << "Error: Vectors do not have the same size.";
    ASSERT_EQ(wordsWithEmptyPrefix.size(), 5) << "Error: Vector has incorrect size for empty string.";
    ASSERT_EQ(wordsWithInvalidPrefix.size(), 0) << "Error: Vector is not empty when it should be.";
    ASSERT_EQ(wordsWithUpperPrefix.size(), 0) << "Error: Vector is not empty when it should be.";
}

/// @brief This tests the copy constructor and copy assignment. There is an original
/// Trie, a copied Trie using the copy constructor, and a copied Trie using the copy
/// assignment. Three vectors from the three different Tries are generated using the
/// allWordsStartingWithPrefix method, and if their sizes are not the same, this is
/// how we know that the copying failed.
TEST(TrieTest3, CheckRuleOfThree)
{
    Trie trie;
    trie.addWord("cat");
    trie.addWord("catastrophe");
    vector<string> wordsWithPrefixCat = trie.allWordsStartingWithPrefix("cat");

    Trie trieCopy(trie);
    vector<string> copyWordsWithPrefix = trieCopy.allWordsStartingWithPrefix("cat");

    Trie trieAssign;
    trieAssign = trie;
    vector<string> assignWordsWithPrefix = trieAssign.allWordsStartingWithPrefix("cat");

    ASSERT_EQ(wordsWithPrefixCat.size(), copyWordsWithPrefix.size()) << "Error: Failed to copy values";
    ASSERT_EQ(wordsWithPrefixCat.size(), assignWordsWithPrefix.size()) << "Error: Failed to assign values";

}

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
