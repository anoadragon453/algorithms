// MST - Find a minimum spanning tree for the vertex and edges of the given graph
//

#include "graph.h"
#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

int main(int argc, char **argv)
{  
    // Get the number of verticies and edges in the
    // input
    int numVerts, numEdges;
    cin >> numVerts;
    cin >> numEdges;

    // Create new graph
    Graph g(numVerts);

    // Loop through edges and weights and add each one
    // to our graph
    for (int i = 0; i < numEdges; i++)
    {
        int vertOneID, vertTwoID, weight;
        cin >> vertOneID;
        cin >> vertTwoID;
        cin >> weight;

        g.insertWeightedEdge(vertOneID, vertTwoID, weight);
    }

    // Print the MST
    g.printMST(0); // Use 0 as the root

    return 0;
}

