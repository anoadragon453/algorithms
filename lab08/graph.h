#include <iostream>
#include <list>
#include <stack>
#include <vector>
using namespace std;
 
class Graph
{
    int V;    // No. of vertices
    list<int> *adj;    // An array of adjacency lists
    vector<int> *printVector; // Holds numbers for printing
 
    // Fills Stack with vertices (in increasing order of finishing
    // times). The top element of stack has the maximum finishing 
    // time
    void fillOrder(int v, bool visited[], stack<int> &Stack);
 
    // A recursive function to print DFS starting from v
    void DFSUtil(int v, bool visited[], vector<int> &numVector);
public:
    Graph(int V);
    void addEdge(int v, int w);
 
    // The main function that finds and prints strongly connected
    // components
    void printSCCs();
 
    // Function that returns reverse (or transpose) of this graph
    Graph getTranspose();
};
