#include <iostream>
#include <list>
#include <stack>
#include <vector>
using namespace std;
 
class Graph
{
    // Given vertex count
    int V; 
    
    // An array of adjacentListsacency lists
    list<int> *adjacentLists;

    // Holds numbers for printing
    vector<int> *printVector;
 
    // Fills stack with vertices in ascending order
    void fillOrder(int v, bool visited[], stack<int> &Stack);
 
    // A recursive function to print DFS starting from v
    void DepthSearch(int v, bool visited[], vector<int> &numVector);
public:
    Graph(int V);
    void pushEdge(int v, int w);
 
    // Finds and prints SCCs
    void printSCCs();
 
    // Returns transpose
    Graph transpose();
};
