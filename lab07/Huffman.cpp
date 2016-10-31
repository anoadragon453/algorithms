#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>

using namespace std;

#define INPUT_LENGTH 6

struct Node {
    int symbol = 0;
    int probability = 0;
    Node* leftChild = NULL;
    Node* rightChild = NULL;
};

void printNodes (Node *node)
{
    char letters[INPUT_LENGTH] = {'A', 'B', 'C', 'D', 'E', 'F'};
    string codes[INPUT_LENGTH];

    // Figure out node codes
    for (int i = 0; i < INPUT_LENGTH; i++)
    {
        cout << node->probability << endl;
        node = node->rightChild;
        
        /*
        if (something)
            codes[i]+="1";
        else
            codes[i]+="0";
        */
    }

    return;

    // Print out nodes and their codes
    for (int i = 0; i < INPUT_LENGTH; i++)
    {
        cout << letters[i] << ":" << codes[i] << endl;
    }

}

void huffman (vector<Node*> *queueOne)
{
    // Create second queue
    vector<Node*> *queueTwo = new vector<Node*>;

    // Move first element from queueOne into queueTwo
    // So queueTwo isn't NULL initially
    queueTwo->push_back(queueOne->front()); // Not working
    queueOne->erase(queueOne->begin());

    // QueueOne is our initial queue
    // where nodes with the lowest probability,
    // aka frequency, are given highest priority
    while (queueOne->size() > 0)
    {
        // Get the two nodes with highest priority
        // (lowest probability)
        Node *lowest       = queueOne->front();
        Node *secondLowest = queueTwo->front();

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
        queueTwo->erase(queueTwo->begin());

        // Add the node back to the queue
        queueTwo->push_back(node);

    }

    // queueTwo is left with just the root node
    printNodes (queueTwo->front());
}

// Sort based on count sort
vector<Node*> *countsort (vector<Node*> *vec, int maxnum)
{
    // Create new 2D vector
    //vector<Node*> *newVec = new vector<Node*>;

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

    // DEBUG: Print out (supposedly) sorted probability
    for (ulong i = 0; i < vec->size(); i++)
    {
        cout << B->at(i)->probability << endl;
    }

    return B;
}

int main(int argc, char **argv)
{  
    // Read in numbers from file
    int letterAmt = 6;
    int maxnum = 0;
    int num;

    // Fill vector with letter frequencies
    vector<Node*> *input = new vector<Node*>;
    for (int i = 0; i < letterAmt; i++)
    {
        cin >> num;

        // Setup new node
        Node *node = new Node;
        node->symbol = i;
        node->probability = num;
        node->leftChild = NULL;
        node->rightChild = NULL;

        // Insert into vector
        input->push_back(node);

        // Check for max probability
        if (num > maxnum)
            maxnum = num;
    }

    // Sort nodes from lowest to highest probability 
    // and calculate huffman codes
    huffman(countsort (input, maxnum));

    return 0;
}

