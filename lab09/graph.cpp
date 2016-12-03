#ifndef GRAPH_CPP
#define GRAPH_CPP

#include "graph.h"
#include <list>
#include <stack>
#include <climits>

using namespace std;

Graph::Graph(int numVerts)
{
    this->numVerts = numVerts;

    // Create 2D vector of nV x nV size
    // filled with zeros
    for ( int i=0; i<numVerts; i++ ) {
        // Create inner vector
        vector<int> innerVector;
        weightVector.push_back(innerVector);
        for ( int j=0; j<numVerts; j++ ) {
            weightVector.at(i).push_back(0);
        }
    }
}

void Graph::insertWeightedEdge(int vertOne, int vertTwo, int weight)
{
    // Insert in both directions
    weightVector[vertTwo][vertOne] = weight;
    weightVector[vertOne][vertTwo] = weight;
}

void Graph::printWeightedGraph()
{
    // Print out the 2D vector graph
    for ( int i=0; i<numVerts; i++ ) {
        for ( int j=0; j<numVerts; j++ ) {
            cout << weightVector.at(i).at(j) << "\t";
        }
        cout << endl;
    }
}

// Find adjacentNodes to the givenNode
vector<int> Graph::adjacentNodes(node givenNode)
{
    // Create a new vector<int>
    vector<int> returnVector;

    // Loop through inner 2D vector at index of givenNode
    for (int i = 0; i < numVerts; i++)
    {
        // For any weights that are higher than zero,
        // that means we have a connection and to place the node
        // we are connected to into the vector of node*'s
        if (weightVector.at(givenNode.nodeID).at(i) > 0)
            returnVector.push_back(i);
    }

    return returnVector;
}

// Return the weight between two nodes
int Graph::weightBetween(node nodeOne, node nodeTwo)
{
    return weightVector.at(nodeOne.nodeID).at(nodeTwo.nodeID);
}

/*
void Graph::printMST(int root)
{
    // Print the MST starting from given root node
    //
    
    // Visit the root initially
    visit(root);

    root++;

    while (root < numVerts)
    {
        // Output the index value of each node as
        // we "visit" it
        
        // Find the nodes this root is next to
        int lowestWeightedNode = -1;
        int lowestWeight = INT_MAX;

        for (int i = 0; i < numVerts; i++)
        {
            // Find the lowest weighted root that hasn't
            // already been visited
            int weight = weightVector.at(root).at(i);
            if (weight != 0) // Only get nodes with a weight
            {
                if (visitedNodes.count(i) && weight < lowestWeight)
                {
                    lowestWeightedNode = i;
                    lowestWeight = weight;
                }

            }
        }

    }
    
}
*/ 

#endif
