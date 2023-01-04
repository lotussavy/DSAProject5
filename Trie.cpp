#include "Trie.h"

/*	Function:  Default constructor
                -- Creates an object of the Trie class with default values.
	Inputs:    void
	Returns:   void
	Side effects:  The new object of Trie Class is initialized which has
                    numNodes=0, count=0 and root=nullptr            
*/
Trie::Trie()
{
    numNodes=0;
    root=nullptr;
    numWords=0;
}



/*	Function:  Destructor
                -- Release the memory allocated to the object of Trie Class.
	Inputs:     void
	Returns:   void
	Side effects:  Destroy the objects by releasing the allocated memory.             
*/
Trie::~Trie()
{
  deleteAll(root);
}


/* Function: deleteAll
            --Helper function to implement the destructor
    Inputs: Reference to the TrieNode(TrieNode*)
    Returns: Nothing
    Side effects: Delete all the nodes of the Trie freeing the memory
*/
void Trie::deleteAll(TrieNode* curNode) 
{
    for (int i = 0; i < 26; i++) 
    {
        if (curNode->characerPointers[i]!=nullptr) 
        {
          deleteAll(curNode->characerPointers[i]);
        }
    }
    //cout<<curNode;
    delete curNode;
    //cout<<"deleted\n";
}




/*	Function:  insert
                -- add word to the Trie
	Inputs:    word-- value to be inserted in to the Trie(string)
	Returns:   True if the word is inserted successfully, false otherwise
	Side effects:  New word is inserted in to Trie creating new Trie nodes and value of numNodes and numWords are updated
*/
bool Trie::insert(string word)
{
  if(root==nullptr)
  {
    root=new TrieNode();
  }
  TrieNode* current=root;
  bool success=false;
  int wLength=word.length();
  for(int i=0;i<wLength;i++)
  {
    int position=word[i]-'a';
    if(!current->characerPointers[position])
    {
      TrieNode* newTrieNode= new TrieNode();
      current->characerPointers[position]=newTrieNode;
      numNodes++;
    }
    current=current->characerPointers[position];
  }
  if (!current->endOfWord)
  {
    numWords++;
    success=true;
  }
  current->endOfWord=true;
  return (success);
}




/* Function: count
        Inputs: void
        Returns: The number of words in the Trie(int)
*/
int Trie::count()
{
  return(numWords);
}




/*	Function:  getSize
                -- find the size of the Trie
	Inputs:    void
	Returns:   number of nodes in the Trie (int)
*/
int Trie::getSize()
{
    return(numNodes);
}



/* Fuction: find
            -- find the word in the given Trie
    Inputs: word to be searched(string)
    Returns: True if the word is found, false otherwise
*/
bool Trie::find(string word)
{
  bool result;
  // return false if Trie is empty
  if (root == nullptr) 
  {
    return false;
  }
  TrieNode* current = root;
  for (int i = 0; i < word.length(); i++)
  {
    int position=word[i]-'a';
    if(current->characerPointers[position]==nullptr)
    {
      return false;
    }
    current=current->characerPointers[position];
  }
  //result=current->endOfWord && current!=nullptr;
  result=current->endOfWord;
  return (result);
}
 


 /*	Function:  completeCount
                -- find the number of words with the given inputs
	Inputs:    input to be searched for(string)
	Returns:   number of words that begin with the given string in the Trie (int)
*/
int Trie::completeCount(string search)
{
  int count=0;
  if (search=="")
  {
    //cout<<"I am empty";
    return count; // Return from here if search string is empty one
  }
  TrieNode *current=root;
  for(int i=0;i<search.length();i++)
  {
    int position=search[i]-'a';
    if(!current->characerPointers[position])
    {
      return count;
    }
    current=current->characerPointers[position];
  }
  int morePointers=0;
  for(int i=0;i<26;i++)
  {
    if(current->characerPointers[i])
    {
      morePointers=1;
      break;
    }
  }
  if(current==nullptr)
    return count;
  if(!morePointers && current->endOfWord)
  {
    count++;
    return count;
  }
  wordCountForPrefix(current,count,search);
  return(count);
}


/* Function: wordCountForPrefix
            --Helper function to implement the completeCount function
    Inputs: Reference to the TrieNode(TrieNode*), Address of count(int&) and  
            string to be searched for(string)
    Returns: Nothing
    Side effects: count get updated whenever matching word is found in the Trie
*/
void Trie::wordCountForPrefix(TrieNode *current,int &count,string search)
{
  if(current->endOfWord)
  {
    count++;
  }
  int morePointers=0;
  for(int i=0;i<26;i++)
  {
    if(current->characerPointers[i])
    {
      morePointers=1;
      break;
    }
  }
  if(!morePointers)
    return;
  for(int i=0;i<26;i++)
  {
    if(current->characerPointers[i])
    {
      search.push_back(97+i);
      wordCountForPrefix(current->characerPointers[i],count,search);
      search.pop_back();
    }
  }
}



/* Function: complete
            --return the vector of the values for the given starting string
    Inputs: string to be searched for(string)
    Returns: vector of values of the words starting with the given string
    Side effects: Vector of the values is returned if no values are found empty vector is returned
*/
vector<string> Trie::complete(string search)
{
  vector<string> list;
  if (search=="")
  {
    //cout<<"I am empty";
    return list; // Return from here if search string is empty one
  }
  
  TrieNode *current=root;
    for(int i=0;i<search.length();i++)
    {
        int position=search[i]-'a';
        if(!current->characerPointers[position])
        {
          //cout<<"No matching first character";
          return list; // When first character pointer is not there
        }
        current=current->characerPointers[position];

    }
    int flagMorePointers=0;
    for(int i=0;i<26;i++)
    {
        if(current->characerPointers[i])
        {
            flagMorePointers=1;
            break;
        }
    }
    // if(current==NULL)
    //     return list;
    if(!flagMorePointers&&current->endOfWord)
    {
        // return form here if no character pointers are there from the last node of search string
        //cout<<search<<endl<<"Just the search string";
        list.push_back(search);
        return list;
    }

  wordSuggestions(current,list,search);
  return list;
}



/* Function: wordSuggestions
            --Helper function to implement the complete function
    Inputs: Reference to the TrieNode(TrieNode*), Address of vector list(vector<string>&) and  
            string to be searched for(string)
    Returns: Nothing
    Side effects: Vector list get updated whenever matching word is found in the Trie
*/
void Trie::wordSuggestions(TrieNode* current,vector<string>& list, string search)
{
    if(current->endOfWord)
    {
      list.push_back(search);
    }
    int morePointers=0;

    for(int i=0;i<26;i++)
    {
        if(current->characerPointers[i])
        {
          morePointers=1;
          break;
        }
    }
    if(!morePointers)
        return ;
    for(int i=0;i<26;i++)
    {
        if(current->characerPointers[i])
        {
            search.push_back(97+i);
            wordSuggestions(current->characerPointers[i],list,search);
            search.pop_back();
        }
    }
 return ;
}