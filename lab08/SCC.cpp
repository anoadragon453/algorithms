// SCC - find strongly connected components of a directed graph
//

#include "graph.h"
#include <iostream>
#include <stdio.h>
#include <vector>
#include <unordered_map>

using namespace std;

int main(int argc, char **argv)
{  
    // Get the number of verticies and edges in the
    // input
    int numVerts, numEdges;
    cin >> numVerts;
    cin >> numEdges;

    // Create instance of our graph object
    Graph graph(numVerts);

    // Loop through edges and add each one to graph
    for (int i = 0; i < numEdges; i++)
    {
        int vertOneID, vertTwoID;
        cin >> vertOneID;
        cin >> vertTwoID;

        graph.addEdge(vertOneID, vertTwoID);
    }

    // Print out SCCs
    graph.printSCCs();

    return 0;
}

