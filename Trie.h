// FILE: Trie.h
// CLASS PROVIDED: Trie
//
// CONSTRUCTORS for the Trie class:
//	Trie()
//		Postcondition: Creates an empty Trie (numNodes == 0,numNodes=0 and root= nullptr)
//
//
// DESTRUCTOR for the Trie class
//	~Trie()
//		Postcondition: Destroys all nodes in the Trie and release the memory associated with the Trie
//
//
// INFORMATIONAL / ACCESSOR MEMBER FUNCTIONS for the Trie class:
//
//   int getSize( )
//     Postcondition: The return value is the number of nodes in the Trie.
//
//  int count()
//     Postcondition: The number of words in the Trie are returned
//
//
//	int completeCount(string search)
//		Postcondition: Number of words in the Trie begining with the given string is returned
//
//
//
//	void wordCountForPrefix(TrieNode* current,int& count, string search)
//		Postcondition: Update the count reference according to the number of words in the trie that begin with search
//
//
//
//	vector<string> complete(string search)
//		Precondtion: string to be searched is given
//		Postcondition: Return vector of the words which starts with the given string
//
//
//
//	void wordSuggestions(TrieNode* current,vector<string>& list, string search)
// 		Postcondition: Update the list reference according to the number of words in the trie that begin with search
//
//
//
//	bool find(string search)
//		Precondition: String to search for in the Trie is given
//		Postcondition: Return true if word exist. Otherwise return false
//
//
// MUTATOR MEMBER FUNCTIONS for the Trie class:
//
//	bool insert( string word )
//		Precondition: word to be inserted is given(string). Duplicates words are not allowed
//		Postcondition: Insert word in the Trie by creating new Nodes. I success return true otherwise false
//						
//


#pragma once

#include <iostream>
#include <exception>
#include<string>
#include<vector>

using namespace std;

class Trie
{

private:
	class TrieNode {
	public:
		TrieNode* characerPointers[26];
		bool endOfWord;

		TrieNode() 
		{
			for (int i = 0; i < 26; i++)
			{
				characerPointers[i]==nullptr;
			}
			endOfWord=false;
		}
		~TrieNode() {}

	};
	
	TrieNode *root;
	int numNodes;   // Number of nodes in the Trie
	int numWords;    //Number of words in the Trie

public:

	Trie();					// creates a Trie
	~Trie();				// destroys the Trie

	bool insert( string word );		// insert the word in the Trie
	int count();  // return the number of words in the Trie
	int getSize(); // return the number of nodes in the Trie
	bool find(string word); // find the word in the Trie
	int completeCount(string search); // find number of words starting with the string given
	void wordCountForPrefix(TrieNode* current,int& count, string search); //helper function to completeCount()
	vector<string> complete(string search); // return the vectors of string that start with the string given
	void wordSuggestions(TrieNode* current,vector<string>& list, string search); //helper function to complete()
	void deleteAll(TrieNode* curNode); //Helper function for the destructor 
};  // End of class Trie



