// This program output the minimum number of operations required to perform the matrix chain multiplication.
//
#include <iostream>
#include <stdio.h>
#include <vector> // you may use the vector class to represent a matrix, for vector<vector<int>> M;
#include <sys/time.h>
#include <climits>

using namespace std;

vector<vector<int>*> *m = new vector<vector<int>*>,
                     *s = new vector<vector<int>*>;

// S - vector holding val which optimally splits 
// the input matricies - get from maxtrixChainOrder
void printOptimalParens(vector<vector<int>*> *s, int i, int j)
{
    if (i == j)
        cout << "A" << i;
    else 
    {
        cout << "(";
        printOptimalParens(s, i, s->at(i)->at(j));
        printOptimalParens(s, s->at(i)->at(j) + 1, j);
        cout << ")";
    }
}

// P - Vector of ints that we get from stdin 
// S - vector holding val which optimally splits 
// M - m[i,j] = minimum cost required to compute matrix A[i]A[i+1]..A[j]
vector<vector<int>*>* matrixChainOrder (vector<int> *p)
{
    int n = p->size() - 1;
    
    // Fill with temp variables
    for (int i = 0; i < n; i++)
    {
        vector<int> *dummyM  = new vector<int> (n, 0);
        vector<int> *dummyS  = new vector<int> (n, 0);
        m->push_back(dummyM);
        s->push_back(dummyS);
    }

    // Calculate subsequence lengths
    for (int shortLen = 1; shortLen < n; shortLen++)
    {
        for (int i = 0; i < n - shortLen; i++)
        {
            int j = i + shortLen;
            m->at(i)->at(j) = INT_MAX;
            for (int k = i; k < j; k++)
            {
                // Calculate cost
                int cost = m->at(i)->at(k) +
                           m->at(k+1)->at(j) +
                           p->at(i) * p->at(k+1) * p->at(j+1);

                if (cost < m->at(i)->at(j))
                {
                    m->at(i)->at(j) = cost;
                    
                    // Index of optimal split index
                    s->at(i)->at(j) = k;
                }
            }
        }
    }

    return s;
}

int main(int argc, char **argv)
{  
    // Get number of matrices in the input:
    int size;
    int num;
    cin >> size;

    // Fill vector with matrix constants from input
    vector<int> *input = new vector<int>;
    for (int i = 0; i <= size; i++)
    {
        cin >> num;
        input->push_back(num);
    }

    // Calculate faster method of calculation
    vector<vector<int>*> *s = matrixChainOrder(input);

    // Print out the cost and resulting function
    cout << m->at(0)->at(s->size() - 1) << endl;
    printOptimalParens (s, 0, s->size() - 1);
    cout << endl;

    return 0;
}

