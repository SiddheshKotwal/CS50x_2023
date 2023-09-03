// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <cs50.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 500;
int num_words = 0;

// Hash table
struct node *table[N];
void hashtable()
{
    for (int i = 0; i < N; i++)
    {
        // allocating memory for each node in the hashtable
        table[i] = malloc(sizeof(node));
        table[i]->next = NULL;
    }
}

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // hashing the word to get hashtable index
    int hashed = hash(word);
    // assigning cursor node to the first node of linked list
    node *cursor = table[hashed]->next;
    while (cursor != NULL)
    {
        // checking if the word matches the dictionary word insensitive of case
        if (strcasecmp(cursor->word, word) == 0)
        {
            // word is found in dictionary return true
            return true;
        }
        // pointing to the next node in the linked list
        cursor = cursor->next;
    }
    // word not found in the dictionary
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    unsigned int value = 0;
    unsigned int key_len = strlen(word);
    for (int i = 0; i < key_len; i++)
    {
        value = value + 37 * tolower(word[i]);
    }
    value = value % N;
    return value;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    hashtable();
    // open a file for reading
    FILE *infile = fopen(dictionary, "r");
    if (dictionary == NULL)
    {
        return false;
    }
    // buffer to store the words from dictionary
    char *buffer = malloc(LENGTH + 1);

    int counter = 0;
    // iterate through all words inside dictionary one at a time
    while (fscanf(infile, "%s", buffer) != EOF)
    {
        counter++;
        // creating a new node for each word
        node *new = malloc(sizeof(node));
        //copying the word into our new node
        strcpy(new->word, buffer);
        new->next = NULL;
        // getting the hashed value from hash function to store in hash table
        int hashed = hash(buffer);
        // making a linked list at every node in the hash table

        node *tmp = table[hashed]->next;
        table[hashed]->next = new;
        new->next = tmp;
    }
    num_words = counter;
    free(buffer);
    fclose(infile);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // returning total number of words in dictionary
    return num_words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    int i;
    // iterating through all the nodes in the hashtable
    for (i = 0; i < N; i++)
    {
        // temporary node
        node *cursor = table[i]->next;
        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            // freeing all the nodes in linked list of hashtable
            free(tmp);
        }
    }

    for (int j = 0; j < N; j++)
    {
        free(table[j]);
    }

    if (i == N)
    {
        //Hashtable freed completely
        return true;
    }
    else
    {
        // Hashtable not freed completely
        return false;
    }
}
