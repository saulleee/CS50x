// Implements a dictionary's functionality

#include <stdbool.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node {
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Counter
int counter = 0;


// Returns true if word is in dictionary, else false
bool check(const char *word) {
    int hashIndex = hash(word);

    // initializing the trav node
    // but i think you don't have to do this, if you just make node *trav = table[hashIndex]
    // node *trav = malloc(sizeof(node));
    // if (!trav) {
    //     printf("NULL\n");
    //     return false;
    // }
    node *trav = table[hashIndex]; // trav is assigned as the first node of table[hashIndex]

    // while (trav->next != NULL) {
    while (trav != NULL) {
        if (strcasecmp(trav->word, word) == 0) {
            return true;
        }
        else {
            trav = trav->next;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word) {
//     int hashValue = 0;
//     char upperCaseLetter = toupper(word[0]);
//     hashValue = upperCaseLetter - 'A';
//     return hashValue;
// }
    unsigned long hash = 5381;
    int c;
    while ((c = toupper(*word++)))
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary) {
    FILE *dictionaryFile = fopen(dictionary, "r");

    if (!dictionary) {
        printf("Could not open file.\n");
        return false;
    }

    // setting up word to use in the while loop below
    // all i care is that the while loop keeps writing over the "word" here over and over
    char word[LENGTH + 1];
    // char *word = malloc(sizeof(char) + 1);
    // if (!word) {
    //     printf("NULL\n");
    //     return false;
    // }

    // instantiating the hash table ???
    // from reddit: "If your hashtable is declared globally, it will be initialized to 0 by default"
    // why don't they mention these things in class???

    while (fscanf (dictionaryFile, "%s", word) != EOF) {
        // fscanf(dictionaryFile, "%s", word);
        // having the above means that we're calling fscanf twice, and so skipping every other word

        // setting the new node to assign it the word
        node *n = malloc(sizeof(node));
        if (!n) {
            printf("NULL\n");
            return false;
        }
        strcpy(n->word, word);
        // from <https://medium.com/@dentured/cs50-2020-pset-5-speller-c9d05afc490>
        int hashIndex = hash(word);
        n->next = table[hashIndex];
        table[hashIndex] = n;
        counter++;

        // n->next = NULL;

        // indexing the node into the table
        // the hash is a function defined above
        // int hashIndex = hash(n->word);
        // if (table[hashIndex] == NULL) {
        //     table[hashIndex] = n;
        //     counter++;
        // }
        // else {
        //     n->next = table[hashIndex];
        //     table[hashIndex] = n;
        //     counter++;
        // }
    }

    // free(word);
    fclose(dictionaryFile);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void) {
    if (counter > 0)
        return counter;
    else
        return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void) {
    for (int i = 0; i < N; i++) {
        // initializing the trav node
        node *trav = malloc(sizeof(node));
        if (!trav) {
            printf("NULL\n");
            return false;
        }

        node *temp = malloc(sizeof(node));
        if (!temp) {
            printf("NULL\n");
            return false;
        }

        trav = table[i];
        while (trav->next != NULL) {
            temp = trav;
            trav = trav->next;
            free(temp);
        }

        free (trav);
    }

    return true;
}