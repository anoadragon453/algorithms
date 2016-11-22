#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;
 
class Graph
{
    public:
        // Constructor
        Graph(int numVerts);

        // Indicates the number of verticies this graph has
        int numVerts;

        // Root node of the graph
        int root;

        // Inserts a graph with weight into the graph
        void insertWeightedEdge(int vertOne, int vertTwo, int weight);

        // Print out the weight 2d graph
        void printWeightedGraph();

        // Print MST
        void printMST(int root);
    private:
        vector<vector<int>> weightVector;

        unordered_map<int, int> visitedNodes;

        void visit(int node);
};
