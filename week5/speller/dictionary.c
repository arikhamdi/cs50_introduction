// Implements a dictionary's functionality

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>


#include "dictionary.h"

// Open dictionary file
// Read strings from file one at a time
// Create a new node for each word
// Hash word to obtain a hash value
// Insert node into hash table at that location


// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false (Case insensitive)
bool check(const char *word)
{
    // Hash word to obtain a hash value
    // Access linked list at that index in the hash table
    // Travers linked list, looking for the word (strcasecmp)
    // cursor = cursor->next;
    // Keep moving cursor until you get to NULL, checking each node for th word
    int index = hash(word);
    for (node *tmp = table[index]; tmp != NULL; tmp = tmp->next)
        {
            if (strcasecmp(word, tmp->word) == 0)
            {
                return true;
            }
        }
    return false;
}

// Hashes word to a number
// Takes a word as input, with alphabetical characters and (possibly) apostrophes
// Outputs a number(index between 0 and N - 1, inclusive) corresponding to wich "bucket" to store the word in
// Deterministic
unsigned int hash(const char *word)
{
    if(isupper(word[0]))
    {
        return word[0] - 65;
    }

    return word[0] - 97;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Open dictionary file
    // Use fopen
    // check if return value is NULL

    FILE *file = fopen(dictionary, "r");
    if(file == NULL)
    {
        return false;
    }
    // fscanf(file, "%s", word)
    // fscanf will return EOF once it reaches end of file
    char *word = malloc(LENGTH + 1 * sizeof(char));
    while (fscanf(file, "%s", word) != EOF)
    {
        // Create a new node
        // malloc
        // Check if return value NULL
        // Copy word into node using strcpy
        node *n = malloc(sizeof(node));
        if(n == NULL)
        {
            return false;
        }
        strcpy(n->word, word);

        // Hash Word
        // Use hash function
        // function takes a string and returns a index
        int index = hash(n->word);

        if(table[index] == NULL)
        {

            n->next = NULL;
        }
        else
        {

            n->next = table[index];
        }

        // Insert Node into hash table
        // hash table is an array of linked lists
        // Set pointers in the correct order

        //n->next = table[index];
        table[index] = n;
    }
    fclose(file);
    free(word);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    int cpt = 0;
    for (int i = 0; i < N; i++)
    {
        for (node *tmp = table[i]; tmp != NULL; tmp = tmp->next)
        {
            cpt++;
        }
    }
    return cpt;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        while (table[i] != NULL)
        {
            node *tmp = table[i]->next;
            free(table[i]);
            table[i] = tmp;
        }
    }
    return true;
}
