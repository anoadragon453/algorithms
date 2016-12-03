#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include "structs.h"

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

        // Get adjacent neighbors to node
        vector<int> adjacentNodes(node givenNode);

        // Get weight between two nodes
        int weightBetween(node nodeOne, node nodeTwo);
    private:
        vector<vector<int>> weightVector;
};

#endif
