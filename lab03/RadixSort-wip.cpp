#include <iostream>
#include <stdlib.h> 
#include <vector>
using namespace std;

#define SEQ_LENGTH 10

vector<vector<int>*> *newVec = new vector<vector<int>*>;

/*
 * Go through each column starting from the right (LSB)
 * Sort the column, but when you move each number up, move the rest of the row with it
 * When you finish going right to left through the whole vector, then it's sorted!
 */

// Sort based on count sort
void countsort (vector<vector<int>*> *vec, int *A, int depth, int maxnum, int length)
{
    // Initializing to 2D vectors...?
    int B[depth];
    int C[maxnum];

    // Initialize histogram with 0's
    for (int i = 0; i <= maxnum; i++)
    {
        C[i] = 0;
    }

    // Count numbers in the array
    for (int i = 0; i < depth; i++)
    {
        C[A[i]]++;
    }

    // C[i] contains number of elements equal to i
    // Take sum of i,i-1
    for (int i = 1; i <= maxnum; i++)
    {
        C[i] = C[i] + C[i-1];
    }

    // Create copy of vec
    newVec->insert(newVec->end(), vec->begin(), vec->end());

    // Check if input is already sorted
    int sorted = true;
    for (int i = 1; i < depth; i++)
    {
        if (A[i] < A[i-1])
        {
            sorted = false;
            break;
        }
    }

    if (sorted)
    {
        cout << "Already sorted!" << endl;
        return;
    }

    // Place each element of A into correct sorted pos in B
    for (int i = depth - 1; i >= 0; i--)
    {
        int index = C[A[i]] - 1;
        B[index] = A[i];
        C[A[i]] = index;

        // Switch the inner vectors
        newVec->at(index) = vec->at(i);
    }

    // Overwrite A with B
    for (int i = 0; i < depth; i++)
    {
        A[i] = B[i];
    }

    // Overwrite vec with newVec
}

void radixsort (vector<vector<int>*> *vec, int depth, int length)
{
    int keyCount = 0, maxnum = 0;
    int count[depth];

    // Initialize count array to 0s
    for (int i = 0; i < depth; i++)
    {
        count[i] = 0;
    }
    
    // Iterate through columns 
    for (int i = length - 1; i >= 0 ; i--)
    {
        for (int j = 0; j < depth; j++)
        {
            if (vec->at(j)->at(i) > maxnum)
                maxnum = vec->at(j)->at(i); 
            count[j] = vec->at(j)->at(i);
        }

        // Perform count sort
        countsort(vec, count, depth, maxnum, length);

        /*
        cout << "newVec after: " << endl;
        for ( int i=0; i<depth; i++ ) {
            for ( int j=0; j<length; j++ ) {
                cout << newVec->at(i)->at(j) << ";";
            }
            cout << endl;
        }
        */

        maxnum = 0;
    }
}

int main(int argc,char **argv)
{
    int depth;
    int length = SEQ_LENGTH;

    // Get the depth of the matrix
    cin >> depth;

    // Create complete 2D vector 
    vector<vector<int>*> *vec = new vector<vector<int>*>;

    // Read in the sequence
    for ( int i=0; i<depth; i++ ) {
        // Create inner vector to be placed in 2D vector
        vector<int>* innerVector = new vector<int>;
        vec->push_back(innerVector);
        for ( int j=0; j<length; j++ ) {
            int tempNum = 0;
            cin >> tempNum;
            vec->at(i)->push_back(tempNum);
        }
    }

    // Run radixsort on the 2D vector
    radixsort(vec, depth, length);

    // Output the result
    for ( int i=0; i<depth; i++ ) {
        for ( int j=0; j<length; j++ ) {
            cout << newVec->at(i)->at(j) << ";";
        }
        cout << endl;
    }
}
