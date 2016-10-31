#include <iostream>
#include <stdlib.h> 
#include <vector>
using namespace std;

#define SEQ_LENGTH 10

// Sort based on count sort
vector<vector<int>*> * countsort (vector<vector<int>*> *vec, int *A, int depth, int maxnum, int length)
{
	// Create new 2D vector
	vector<vector<int>*> *newVec = new vector<vector<int>*>;

    // Initialize histogram and holding arrays
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

	vec = new vector<vector<int>*>;
	vec->insert(vec->end(), newVec->begin(), newVec->end());

	return vec;

}

vector<vector<int>*> * radixsort (vector<vector<int>*> *vec, int depth, int length)
{
    int keyCount = 0, maxnum = 0;

    // Iterate through columns 
    for (int i = length - 1; i >= 0 ; i--)
    {
		int count[depth];
        for (int j = 0; j < depth; j++)
        {
            if (vec->at(j)->at(i) > maxnum)
                maxnum = vec->at(j)->at(i); 
            count[j] = vec->at(j)->at(i);
        }

        // Perform count sort
        vec = countsort(vec, count, depth, maxnum, length);

        maxnum = 0;
    }

	return vec;
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
    vec = radixsort(vec, depth, length);

    // Output the result
    for ( int i=0; i<depth; i++ ) {
        for ( int j=0; j<length; j++ ) {
            cout << vec->at(i)->at(j) << ";";
        }
        cout << endl;
    }
}
