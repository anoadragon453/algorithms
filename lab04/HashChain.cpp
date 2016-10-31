#include "HashTable.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <vector>
#include <list>
#include <iostream>

using namespace std;

HashTable *table;

void swap(int *seq, int first, int second)
{
    int scratch = seq[second];
    seq[second] = seq[first];
    seq[first] = scratch;
}

void hashchain(string userInput)
{
    // Get the first character of the user's input
    string i = userInput.substr(0,1);

    if (!i.compare("e"))
        exit(EXIT_SUCCESS);
    else if (!i.compare("i"))
    {
        int key = 0;
        if (userInput.length() > 1)
            key = stoi(userInput.substr(1,2));

        // Error if no key
        if(key == 0)
        {
            cout << "Missing key after 'i'" << endl;
            return;
        }

        // Insert key into hashtable
        table->insert(key);
    }
    else if (!i.compare("d"))
    {
        int key = 0;
        if (userInput.length() > 1)
            key = stoi(userInput.substr(1,2));

        // Error if no key
        if(key == 0)
        {
            cout << "Missing key after 'd'" << endl;
            return;
        }

        // Delete key from hashtable
        if (table->remove(key))
            cout << key << ":DELETED;" << endl;
        else
            cout << key << ":DELETE_FAILED;" << endl;

    }
    else if (!i.compare("s"))
    {
        int key = 0;
        if (userInput.length() > 1)
            key = stoi(userInput.substr(1,2));

        // Error if no key
        if(key == 0)
        {
            cout << "Missing key after 's'" << endl;
            return;
        }

        // Search for key in hashtable
        hashListIndex index = table->search(key);
        if (index.hashIndex == -1)
            cout << key << ":NOT_FOUND;" << endl;
        else
            cout << key << ":FOUND_AT" << index.hashIndex << "," << index.listIndex << ";" << endl;

    }
    else if (!i.compare("o"))
    {
        // Output hashmap contents
        table->print();
    }
    else
        cout << "Unknown command: " << i << endl;
}

int main(int argc,char **argv)
{
    int tableSize = 0;
    cin >> tableSize;
    table = new HashTable(tableSize);

    string userInput;
    // Read in user input
    while (true)
    {
        //cout << "$ ";
        cin >> userInput;
        hashchain(userInput);
    }
}
