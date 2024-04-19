#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

struct TrieNode {
  struct TrieNode* children[ALPHABET_SIZE];
  int isEndOfWord;
};

struct TrieNode* getNode(void) {
  struct TrieNode* pNode = NULL;
  pNode = (struct TrieNode*)malloc(sizeof(struct TrieNode));

  if (pNode) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
      pNode->children[i] = NULL;
    }
    pNode->isEndOfWord = 0;
  }

  return pNode;
}

// Trie structure
struct Trie
{
struct TrieNode* root;
};

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
struct TrieNode* pCrawl = pTrie->root;
  for (int i = 0; word[i]; i++) {
    int index = word[i] - 'a';
    if (!pCrawl->children[index]) {
      pCrawl->children[index] = getNode();
    }
    pCrawl = pCrawl->children[index];
  }
  pCrawl->isEndOfWord = 1;    
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
struct TrieNode* pCrawl = pTrie->root;
  for (int i = 0; word[i]; i++) {
    int index = word[i] - 'a';
    if (!pCrawl->children[index]) {
      return 0; 
    }
    pCrawl = pCrawl->children[index];
  }
  return pCrawl->isEndOfWord;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
  if (pTrie) {
    freeTrieNode(pTrie->root);
    free(pTrie);
  }
  return NULL;
}

// Initializes a trie structure
struct Trie *createTrie()
{
struct Trie* newTrie = (struct Trie*)malloc(sizeof(struct Trie));
  newTrie->root = NULL;
  return newTrie;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
FILE* fp = fopen(filename, "r");
  if (fp == NULL) {
    printf("Error opening file: %s\n", filename);
    return -1;
}
}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}