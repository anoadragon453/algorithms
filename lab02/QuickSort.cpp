#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

// Swap contents of array based on indicies
void swap(int *seq, int first, int second)
{
    int scratch = seq[second];
    seq[second] = seq[first];
    seq[first] = scratch;
}

int partition(int *seq, int low, int high, bool flipSwitch)
{
    int pivot;
    if (flipSwitch)
    {
        // Get random number from seq's low to high
        pivot = (int) (low + (rand() % (high - low)));

        // Swap random indicies' content
        swap(seq, high, pivot);

        // Flip the switch off
        flipSwitch = !flipSwitch;
    }

    pivot = seq[high];

    int i = low;
    int j = i;

    // Loop through subarray 
    for (;j <= high - 1;j++)
    {
        // Check if value is higher than pivot
        if (seq[j] <= pivot)
        {
            swap(seq, i, j);
            i++;
        }
    }
    swap(seq, i, high);
    return i;
}

void quicksort(int *seq, int pivot, int size, bool flipSwitch)
{
    // End recursion if pivot >= size
    if (pivot < size)
    {
        int newSize = partition(seq, pivot, size, flipSwitch);
        quicksort(seq, pivot, newSize - 1, false);
        quicksort(seq, newSize + 1, size, false);
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
    quicksort(Sequence, 0, arraySize-1, true);

    // Output the result
    for(int i=0; i<arraySize; i++)
        cout << Sequence[i] << endl;

    // Free allocated space
    delete[] Sequence;
}
