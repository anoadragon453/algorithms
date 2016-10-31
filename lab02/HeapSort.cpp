#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

enum nodeType { PARENT, LEFT, RIGHT };

void swap(int *seq, int first, int second)
{
    int scratch = seq[second];
    seq[second] = seq[first];
    seq[first] = scratch;
}

int getNode(int index, int nodeType)
{
    switch (nodeType)
    {
        case PARENT:
            return (index - 1)/2;
        case LEFT:
            return 2*index + 1;
        case RIGHT:
            return 2*index + 2;
    }
}

/* Float nodes down the subtree */
void maxHeapify(int *seq, int start, int heapsize)
{
    int leftChild = getNode(start, LEFT);
    int rightChild = getNode(start, RIGHT);

    /* Sift the parent down if it's smaller than one of it's children */
    int largest = seq[start];
    if (leftChild <= heapsize && seq[leftChild] > seq[start])
        largest = leftChild;    
    else
        largest = start;
    if (rightChild <= heapsize && seq[rightChild] > seq[largest])
        largest = rightChild;
    if (largest != start)
    {
        swap(seq, largest, start);
        maxHeapify(seq, largest, heapsize);
    }
}

/* Create a set of heaps */
void buildMaxHeap(int *seq, int size)
{
    int heapsize = size;
    int i = ((size+1)/2)-1;
    for(;i >= 0;i--)
    {
        maxHeapify(seq, i, heapsize);
    }
}

void heapsort(int *seq, int size)
{
    int heapsize = size;
    buildMaxHeap(seq, size);
    for (int i = size; i >= 1; i--) 
    {
        swap(seq, i, 0);
        heapsize--;
        maxHeapify(seq, 0, heapsize);
    }
}

int main(int argc,char **argv)
{
    int *Sequence;
    int arraySize;

    // Get the size of the sequence
    cin >> arraySize;

    // Allocate enough memory to store "arraySize" integers
    Sequence = new int[arraySize];

    // Read in the sequence
    for ( int i=0; i<arraySize; i++ )
        cin >> Sequence[i];

    // Run your algorithms to manipulate the elements in Sequence
    heapsort(Sequence, arraySize-1);

    // Output the result
    for(int i=0; i<arraySize; i++)
        cout << Sequence[i] << endl;

    // Free allocated space
    delete[] Sequence;
}
