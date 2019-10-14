/*
1<=T<=20
1<=N<=20
N strings
str to be searched
*/

#include "Functions.h"

#define Alphabet 26
#define LEN 256

typedef struct TrieNode
{
	struct TrieNode* child[Alphabet];
	int isWord;

}TrieNode;

int isLeaf(TrieNode* root)
{
	for (int i = 0; i < Alphabet; i++)
	{
		if (root->child[i])
			return 0;
	}
	return 1;
}

void delete(TrieNode* root)
{
	if (!root)
		return;

	for (int i = 0; i < Alphabet; i++)
	{
		if (root->child[i])
		{
			if (isLeaf(root->child[i]))
			{
				free(root->child[i]);
				root->child[i] = NULL;
			}
			else
				delete(root->child[i]);
		}
			
	}

	free(root);
	root = NULL;
	
}

TrieNode* getNode()
{
	TrieNode* temp = (TrieNode*)malloc(sizeof(TrieNode));
	if (!temp)
		return NULL;

	for (int i = 0; i < Alphabet; i++)
		temp->child[i] = NULL;

	temp->isWord = 0;

	return temp;
}

void PrefixKeyStrings(TrieNode* root, char* str, int *count)
{
	if (!root)
		return;
	
	if (root->isWord)
		//printf("%s ", str);
		(*count)++;

	if (isLeaf(root))
		return;

	for (int i = 0; i < Alphabet; i++)
	{		
		if (root->child[i])
		{
			/*int j = 0;
			char* str1 = (char*)malloc(sizeof(char)*(strlen(str)+2));	//1 for coming new char and 1 for NULL
			if (!str1)
				return 0;

			while (str[j])
				str1[j] = str[j++];

			str1[j++] = (char)(i + 'a');
			str1[j] = '\0';

			PrefixKeyStrings(root->child[i], str1, count);

			if (str1)
			{
				free(str1);
				str1 = NULL;
			}*/

			PrefixKeyStrings(root->child[i], str, count);
		}

	}

}

void searchPrefixKey(TrieNode* root, char* str, int len)
{
	if (!str)
		return;

	struct TrieNode* temp = root;
	for (int i = 0; i < len; i++)
	{
		int index = str[i] - 'a';
		if (!temp->child[index])
		{
			printf("0\n");
			return;
		}
		temp = temp->child[index];
	}

	//Now we shall print all words having prefix as str (till len)

	/*char* str1 = (char*)malloc(sizeof(char)*LEN);
	if (!str1)
		return;

	memset(str1, 0, sizeof(char)*LEN);

	for (int i = 0; i < len;i++)
		str1[i] = str[i];*/

	
	//PrefixKeyStrings(temp, str1, &count);

	int count = 0;
	PrefixKeyStrings(temp, str, &count);

	printf("%d\n", count);

	/*if (str1)
	{
		free(str1);
		str1 = NULL;
	}*/
}

void insertKey(TrieNode* root, char *str)
{
	if (!str)
		return;

	int len = strlen(str);

	for (int i = 0; i < len; i++)
	{
		int index = str[i] - 'a';
		if (!root->child[index])
			root->child[index] = getNode();
			
		root = root->child[index];
	}

	root->isWord = 1;
}

void searchKey(TrieNode* root, char *str)
{
	if (!str)
		return;

	int len = strlen(str);

	for (int i = 0; i < len; i++)
	{
		int index = str[i] - 'a';
		if (!root->child[index])
		{
			printf("0\n");
			return;
		}
		root = root->child[index];
	}

	if (root->isWord)
		printf("1\n");
	else
		printf("0\n");
}

void deleteKey(TrieNode* pTrie, char key[])
{

}

void Trie()
{
	FILE *fp = fopen("Test.txt", "r");

	int T;
	fscanf(fp, "%d", &T);

	TrieNode* root = getNode();

	while (T--)
	{
		/*int N;
		fscanf(fp, "%d", &N);*/

		//TrieNode* root = getNode();

		char* func = (char*)malloc(sizeof(char)* 5);
		if (!func)
			return;

		fscanf(fp, "%s", func);

		char *str = (char*)malloc(sizeof(char)*LEN);
		if (!str)
			return;

		fscanf(fp, "%s", str);

		int len = strlen(str);

		if (*func == 'a')	//a for add, why to compare whole string ;)
			insertKey(root, str);

		else //means func is to find
			searchPrefixKey(root, str, len);

		/*for (int i = 0; i < N; i++)
		{
			fscanf(fp, "%s", str);

			insertKey(root, str);

		}*/

		/*int len = strlen(str);

		for (int i = 1; i <= len; i++)
		{
			searchPrefixKey(root, str, i);
			printf("\n");
		}*/

		//searchKey(root, str);

		if (func)
		{
			free(func);
			func = NULL;
		}

		if (str)
		{
			free(str);
			str = NULL;
		}

		//delete(root);
	}

	delete(root);

	fclose(fp);
}