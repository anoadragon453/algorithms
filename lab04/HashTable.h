#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <list>

/* Helper to return multiple variables */
struct hashListIndex {
    int hashIndex;
    int listIndex;
    std::list<int>::iterator listIndexIterator;
};

class HashTable {
    /* Private functions/vars */
    private:
        std::vector<std::list<int>*>* table;
        int hash(int key);
        int length;

    /* Public functions */
    public:
        HashTable();
        HashTable(int length);
       ~HashTable();
        void insert(int key);
        bool remove(int key);
        hashListIndex search(int key);
        void print();
};

#endif
