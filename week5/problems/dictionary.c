// Implements a dictionary's functionality
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 10000;

// Number of words in the dictionary
unsigned int word_count = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Bucket index in hash table
    unsigned int bucket_index = hash(word);

    // Traverse through the linked list
    for (node *cursor = table[bucket_index]; cursor != NULL; cursor = cursor->next)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // djb2 hash function by Daniel J. Berstein adapted for case insensitive
    unsigned int hash = 5381;

    for (const char *ptr = word; *ptr != '\0'; ptr++)
    {
        hash = ((hash << 5) + hash) + tolower(*ptr);
    }

    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open dictionary
    FILE *fpt = fopen(dictionary, "r");
    if (fpt == NULL)
    {
        printf("Could not open the dictionary.\n");
        return false;
    }

    char buffer[LENGTH + 1];

    // Read file till the end
    while (fscanf(fpt, "%s", buffer) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }

        strcpy(n->word, buffer);
        n->next = NULL;

        // Hash the word stored in buffer
        unsigned int hash_index = hash(buffer);

        // Add newly added node to linked list
        n->next = table[hash_index];
        table[hash_index] = n;

        // Update word count for size function
        word_count++;
    }

    fclose(fpt);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Loop through buckets in hash table
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];

        // Free each linked list
        while (cursor != NULL)
        {
            node *tmp = cursor->next;
            free(cursor);
            cursor = tmp;
        }
    }

    return true;
}