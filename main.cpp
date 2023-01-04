/*
Name: Kamal Acharya
UID:U00997907
Project Name:  Building a word autocomplete application using an alphabet trie
Description:
An alphabet trie data structure is implemented.And is used to write an autocomplete 
program using an English dictionary.
Prototypes of the class along with their data and member fucntion are given in the Trie.h. 
The details of all the member fucntion is implemented in the Trie.cpp.
main.cpp is used to test all the function that are implemented.
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>  
#include <stdlib.h>
#include<ios> //used to get stream size
#include<limits> //used to get numeric limits

#include "Trie.h"

using namespace std;

void memoryLeakCheck()
{
	Trie newTrie;
	// string nextWord;
	// // Create an input file stream and open a file 
	// ifstream infile;
	// infile.open("wordList.txt");
	// // If the file couldn't be opened, infile will be false 
	// if (!infile)
	// {
	// 	cout << "Couldn't open file" << endl;
	// 	return ;
	// }
	// //Read lines from the file into nextWord
	// // until we reach the end-of-file marker 
	// while(!infile.eof())
	// {
	// 	getline(infile, nextWord);
	// 	newTrie.insert(nextWord);
	// }
	// infile.close();

	//newTrie.insert("hello");
	//newTrie.insert("apple");
	//newTrie.insert("ball");
	newTrie.insert("a");
}

int main()
{
	Trie newTrie;
	string nextWord;
	// Create an input file stream and open a file 
	ifstream infile;
	infile.open("wordList.txt");
	// If the file couldn't be opened, infile will be false 
	if (!infile)
	{
		cout << "Couldn't open file" << endl;
		return 1;
	}
	//Read lines from the file into nextWord
	// until we reach the end-of-file marker 
	while(!infile.eof())
	{
		getline(infile, nextWord);
		newTrie.insert(nextWord);
	}
	//cout<<newTrie.count()<<endl;
	//cout<<newTrie.getSize()<<endl;
	string prefix;
	cout<<"Please enter a word prefix (or press enter to exit): ";
	getline(cin,prefix);
	while (!prefix.empty())
	{
		string showCompletion;
		cout<<"There are "<<newTrie.completeCount(prefix)<<" completions for the prefix "<< prefix <<".  Show completions? ";
		cin>>showCompletion;
		if (showCompletion=="Yes" || showCompletion=="yes")
		{
			cout<<"Completions"<<endl;
			cout<<"-----------"<<endl;
			vector <string> vec = newTrie.complete(prefix);
			for (vector<string>::iterator it = vec.begin(); it != vec.end(); ++it) 
			{
				cout << *it << endl;
			}
		}
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout<<endl<<"Please enter a word prefix (or press enter to exit): ";
		getline(cin,prefix);
	}

	//string wait;
	//cin>>wait;
	// for (int i = 0; i < 2; i++) // Creating problem while running twice
	// {
	// 	memoryLeakCheck();
	// }
	
	return(0);
 }