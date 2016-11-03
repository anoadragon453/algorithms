#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

#define INPUT_LENGTH 6

char letters[INPUT_LENGTH] = {'A', 'B', 'C', 'D', 'E', 'F'};
unordered_map<char, string> *map; 

struct Node {
    char symbol = 0;
    int probability = 0;
    Node* leftChild = NULL;
    Node* rightChild = NULL;
};

bool isLeaf (Node *node)
{
    return node->leftChild == NULL && node->rightChild == NULL;
}

// Insert correct path to each node into map
void huffmanTreeAdd(Node* node, string path)
{
    if (isLeaf(node))
    {
        pair<int, string> newPair (node->symbol, path);
        map->at(node->symbol) = path;
    }
    else
    {
        huffmanTreeAdd(node->leftChild, path + "0");
        huffmanTreeAdd(node->rightChild, path + "1");
    }
}

void printNodes (Node *node)
{
    // Insert correct codes into map
    huffmanTreeAdd(node, "");
    
    // Print node codes from map
    for (int i = 0; i < INPUT_LENGTH; i++)
    {
        cout << letters[i] << ":" << map->at(letters[i]) << endl;
    }
}

// Sort based on count sort
vector<Node*> *countsort (vector<Node*> *vec, int maxnum)
{
    // Initialize histogram and holding arrays
    vector<Node*> *B = new vector<Node*> (INPUT_LENGTH, NULL);
    int C[maxnum];

    // Initialize histogram with 0's
    for (int i = 0; i <= maxnum; i++)
    {
        C[i] = 0;
    }

    // Count numbers in the array
    for (ulong i = 0; i < vec->size(); i++)
    {
        C[vec->at(i)->probability]++;
    }

    // C[i] contains number of elements equal to i
    // Take sum of i,i-1
    for (int i = 1; i <= maxnum; i++)
    {
        C[i] = C[i] + C[i-1];
    }

    // Place each element of A into correct sorted pos in B
    for (int i = vec->size() - 1; i >= 0; i--)
    {
        int index = C[vec->at(i)->probability] - 1;
        B->at(index) = vec->at(i);
        C[vec->at(i)->probability] = index;
    }

    return B;
}

void huffman (vector<Node*> *queueOne)
{
    while (queueOne->size() > 1)
    {
        // Get the two nodes with highest priority
        // (lowest probability)
        Node *lowest       = queueOne->at(0);
        Node *secondLowest = queueOne->at(1);
        
        // Create new Node with these as children,
        // and probability equal to the sum of the
        // nodes
        Node* node = new Node;
        node->probability = lowest->probability +
                            secondLowest->probability;
        node->leftChild   = lowest;
        node->rightChild  = secondLowest;

        // Remove those two nodes from the array
        queueOne->erase(queueOne->begin());
        queueOne->erase(queueOne->begin());

        // Insert the new node in the correct
        // spot in the queue
        bool insertAtBack = true;
        for (ulong i = 0; i < queueOne->size(); i++)
        {
            if (node->probability < queueOne->at(i)->probability)
            {
                queueOne->insert(queueOne->begin() + i, node);
                insertAtBack = false;
                break;
            }
        }

        // If we didn't find a spot in the array for it.
        // Stick it at the end
        if (insertAtBack)
            queueOne->push_back(node);
    }

    // Print out the tree starting from
    // the root node
    printNodes(queueOne->front());
}

int main(int argc, char **argv)
{  
    // Read in numbers from file
    int letterAmt = 6;
    int maxnum = 0;
    int num;

    // Create new HashTable
    map = new unordered_map<char, string>;

    // Fill vector with letter frequencies
    vector<Node*> *input = new vector<Node*>;
    for (int i = 0; i < letterAmt; i++)
    {
        cin >> num;

        // Setup new node
        Node *node = new Node;
        node->symbol = letters[i];
        node->probability = num;
        node->leftChild = NULL;
        node->rightChild = NULL;

        // Insert into vector
        input->push_back(node);

        // Insert blank path into HashMap
        pair<int, string> newPair (letters[i], "N");
        map->insert(newPair);

        // Check for max probability
        if (num > maxnum)
            maxnum = num;
    }

    // Sort nodes from lowest to highest probability 
    // and calculate huffman codes
    huffman(countsort(input, maxnum));

    return 0;
}

