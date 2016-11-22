#include "graph.h"
#include <list>
#include <stack>
#include <unordered_map>
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

void Graph::visit(int node)
{
    // "Visit" the node
    visitedNodes[node] = 0;
}

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

        // Check to find the lowest weight to connect to one
        // of the previous nodes
        
        cout << lowestWeightedNode << endl;

        // We found a node
        //
        visit(root);

        root++;
    }
    
}
 
