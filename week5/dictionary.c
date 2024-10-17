// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next; // pointer to the address of the next node
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26; // N pointers in hash table below
int word_count = 0;

// Hash table - array of linked lists
node *table[N]; // global pointer array to keep track of the words in the dictionary

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary) // string dictionary - file to open and read to table
{
    // TODO
    // Open the dictionary file
    FILE *source = fopen(dictionary, "r"); //  r = read the words in dictionary

    // Check if return is NULL
    if (source == NULL)
    {
        return false;
    }

    // Read strings in the file
    // fscanf(file, "%s", word);
    char string[LENGTH + 1];                    // null operator in the end of every string
    while (fscanf(source, "%s", string) != EOF) // scan to the end of the string
    {
        // Add each word to the hash table
        // Create space for a new hash table node with malloc
        node *n = malloc(sizeof(node)); // store address of the node

        if (n == NULL) // checj return value
        {
            return false;
        }

        // Copy the word into the new node
        strcpy(n->word, string);

        // Hash the word to obtain its hash value
        int hashNum = hash(string);

        // Insert the new node into the hash table (using the index specified by its hash value)
        if (table[hashNum] == NULL) // if linked list is empty
        {
            n->next = NULL;
        }
        else // if not empty, point n to first node of the linked list
        {
            n->next = table[hashNum];
        }
        // Point header to n
        table[hashNum] = n;
        word_count += 1;
    }
    // Close the dictionary file
    fclose(source);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return word_count;
}

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int hashNum = hash(word); // create a variable

    // cursor variable pointing to head
    node *cursor = table[hashNum];

    // looop until the end of the list
    while (cursor != NULL)
    {
        // Check if the words are the same
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        cursor = cursor->next; // go to the next node
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

void freenode(node *n)
{
    if (n->next != NULL)
    {
        freenode(n->next);
    }
    free(n);
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++) // go through the linked list
    {
        if (table[i] != NULL)
        {
            freenode(table[i]);
        }
    }
    return true;
}
