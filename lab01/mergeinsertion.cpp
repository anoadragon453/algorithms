#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

void insertion(int *seq, int begPoint, int endPoint)
{
  // Loop through the array
  for (int j = begPoint+1; j < endPoint; j++)
  {
    // Check val j against other vals
    int key = seq[j];
    int i = j - 1;
    while (i >= begPoint && seq[i] > key) {
      // Move val until it's larger than other val
      seq[i + 1] = seq[i];
      i--;
    }
    seq[i + 1] = key;
  }
}

void merge(int *seq, int begPoint, int midPoint, int endPoint)
{
  // Get size of given subarrays
  int leftSize = midPoint - begPoint;
  int rightSize = endPoint - midPoint;

  // Create two new arrays
  int *left = new int[leftSize];
  int *right = new int[rightSize];

  // Copy values from given array into new array
  for (int i = 0; i < leftSize; i++)
  {
    left[i] = seq[begPoint + i];
  }

  for (int j = 0; j < rightSize; j++)
  {
    right[j] = seq[midPoint + j];
  }

  // Sort the arrays
  int i = 0,j = 0;
  for (int k = begPoint; k < endPoint; k++)
  {
    // Ensure we don't go out of bounds
    if (i < leftSize && j >= rightSize)
    {
      // j is out of bounds, i wins
      for (; i < leftSize; ++i)
      {
        seq[k++] = left[i];
      }
    }
    else if (i >= leftSize && j < rightSize)
    {
      // i is out of bounds, j wins
      for (; j < rightSize; ++j)
      {
        seq[k++] = right[j];
      }
    }
    else if (i < leftSize && j < rightSize)
    {
      // Check which array holds the smallest value
      if (left[i] < right[j])
      {
        // Move values over, smallest first
        seq[k] = left[i];
        i++;
      } else{
        seq[k] = right[j];
        j++;
      }
    }
    
  }
}

void mergeInsert(int *seq, int begPoint, int endPoint)
{
  int size = endPoint - begPoint;
  if (endPoint - begPoint >= 10)
  {
    // Perform merge sort
    int midPoint= (int)((begPoint + endPoint)/2);
    mergeInsert(seq, begPoint, midPoint);
    mergeInsert(seq, midPoint, endPoint);
    merge(seq, begPoint, midPoint, endPoint);
  } else {
    // Perform insertion sort
    insertion(seq, begPoint, endPoint);
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
  mergeInsert(Sequence, 0, arraySize);

  // Output the result
  for(int i=0; i<arraySize; i++)
      cout << Sequence[i] << endl;

  // Free allocated space
  delete[] Sequence;
}
