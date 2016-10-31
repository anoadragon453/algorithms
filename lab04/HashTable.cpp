#include "HashTable.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

#define DEFAULT_TABLELENGTH 10

using namespace std;

/* Constructor
 *     Initializes hashtable of empty linked lists
 */
HashTable::HashTable()
{
    // Default table length
    int tableLength = DEFAULT_TABLELENGTH;
    
    // Create a new list of lists (hashtable)
    table = new vector<list<int>*>;

    // Fill table with empty linked lists
    for (int i = 0; i < tableLength; i++)
    {
        list<int>* nodeList = new list<int>;
        table->push_back(nodeList);
    }
}

/* Explicit Constructor
 *     Initializes hashtable of empty linked lists
 */
HashTable::HashTable(int tableLength)
{
    if (tableLength <= 0)
        tableLength = DEFAULT_TABLELENGTH;

    // Create a new list of lists (hashtable)
    table = new vector<list<int>*>;

    // Fill table with empty linked lists
    for (int i = 0; i < tableLength; i++)
    {
        list<int>* nodeList = new list<int>;
        table->push_back(nodeList);
    }
}

/* Destructor
 *     Free all memory used by hash table
 */
HashTable::~HashTable()
{
    // Iterate through table lists and delete their contents
    for (int i = table->size() - 1; i >= 0; i--)
    {
        list<int> *currList = table->at(i);

        while (currList->size() > 0)
            currList->pop_front();

        table->pop_back();
    }
}

/* Hash function
 *     Calculates hash based on given key and table size
 */
int HashTable::hash (int key)
{
    return key % table->size();
}

/* Insert
 *     Insert a key into the table
 */
void HashTable::insert (int key)
{
    int hash = HashTable::hash(key);

    // Insert the key at table[hash]'s front
    table->at(hash)->push_front(key);
}

/* Delete
 *     Remove a key from the table 
 */
bool HashTable::remove (int key)
{
    // Search through hashtable for hash,list index
    hashListIndex index = HashTable::search(key);

    if (index.hashIndex == -1)
        return false;

    // Get list containing key and remove key node from it
    table->at(index.hashIndex)->erase(index.listIndexIterator);

    return true;
}

/* Search 
 *     Searches for a key in the table 
 *     Returns index in table and inner list of found element
 */
hashListIndex HashTable::search (int key)
{
    // New hashListIndex object
    hashListIndex index;

    // Start with first val of first list
    int currVal = table->at(0)->front();

    // Iterate through table lists and their contents
    for (int i = 0; i < table->size(); i++)
    {
        list<int> *currList = table->at(i);
        list<int>::iterator it = currList->begin();

        // Index of node we're currently at
        int nodeCount = 0;

        // Iterate over entire list
        for (it = currList->begin();it != currList->end();)
        {
            // Advance one index in the list
            currVal = *it;

            if (currVal == key)
            {
                index.hashIndex = i;
                index.listIndex = nodeCount;
                index.listIndexIterator = it;
                return index;
            }

            if (++it != currList->end())
                nodeCount++;
        }
    }

    // Didn't find it
    index.hashIndex = -1;

    return index;
}

void HashTable::print ()
{
    int currVal = table->at(0)->front();

    for (int i = 0; i < table->size(); i++)
    {
        list<int> *currList = table->at(i);
        list<int>::iterator it = currList->begin();

        cout << i << ":";
        for (it = currList->begin();it != currList->end();)
        {
            currVal = *it;

            // Print out current node in list
            cout << currVal << "->";

            ++it;
        }
        cout << ";" << endl;
    }
}
