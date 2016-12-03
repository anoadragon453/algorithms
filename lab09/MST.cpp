// MST - Find a minimum spanning tree for the vertex and edges of the given graph
//
#ifndef MST_CPP
#define MST_CPP

#include "structs.h"
#include "graph.h"
#include <iostream>
#include <stdio.h>
#include <climits>
#include <vector>
#include <algorithm>

using namespace std;

// Create min priority queue of verticies
vector<node*> pq;
vector<node*> finalNodes;

// Sort using Algorithm
bool compareByWeight(const node* a, const node* b)
{
    return a->weight < b->weight;
}

// Pop the first node of min priority queue
node* extractMin ()
{
    // Get min node from queue
    //
    node* tempNode = pq.at(0);
    node* minNode = new node;
    minNode->nodeID = tempNode->nodeID;
    minNode->parent = tempNode->parent;
    minNode->weight = tempNode->nodeID;

    // Remove min node from the queue
    pq.erase (pq.begin());

    // Return the first node
    return minNode;
}

void pushToVector(node* nodeToPush)
{
    // Push_back the node
    pq.push_back(nodeToPush);
    
    // Rebuild the priority queue 
    sort(pq.begin(), pq.end(), compareByWeight);
}

// Allows you to decrease key in the min-queue
//
// Decrease value of the key of the heap
// Check if we gotta move up, if swap over and over
void decreaseKey (int rootID, int decreaseTo)
{
    // Decrease value of the given node
    //
    
    // Find the requested node in the pq
    for (int i = 0; i < pq.size(); i++)
    {
        node* foundNode = pq.at(i);
        if (foundNode->nodeID == rootID)
        {
            // Decrease it's value
            foundNode->weight = decreaseTo;

            // Remove the node and reshuffle the queue so
            // everything is in it's correct location
            pq.erase(pq.begin() + i);
            pushToVector(foundNode);

            // Break out of the loop
            break;
        }
    }
}

// Initialize our priority queue with the amount of values
void initQueue (int size)
{
    for (int i = 0; i < size; i++)
    {
        node* newNode = new node;
        newNode->nodeID = i;
        newNode->parent = NULL;
        newNode->weight = INT_MAX; // "null"
        finalNodes.push_back(newNode);
        pq.push_back(newNode); 
    }
}

bool contains(vector<node*> vec, node* theNode)
{
    for (int i = 0; i < vec.size(); i++)
    {
      if (vec.at(i)->nodeID = theNode->nodeID)
        return true;
    }

    return false;
}

int main(int argc, char **argv)
{
    // Get the number of verticies and edges in the input
    int numVerts, numEdges;
    cin >> numVerts;
    cin >> numEdges;

    // Initialize min priority queue
    initQueue(numVerts);

    // Decrease key of the root node to 0
    // 0 is always root in this case
    decreaseKey(0, 0); // Set root node weight to 0

    // Create container for graph weights
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

    g.printWeightedGraph();

    // While queue has nodes in it
    while (pq.size() > 0)
    {
        node* extractedNode = extractMin();

        // For each neighbor of extractedNode...
        vector<node*> adjacentNodes;
        vector<int> adjacentNodeIDs = g.adjacentNodes(*extractedNode);
        for (int i = 0; i < adjacentNodeIDs.size(); i++)
        {
          adjacentNodes.push_back(finalNodes.at(adjacentNodeIDs.at(i)));
        }

        for (int i = 0; i < adjacentNodes.size(); i++)
        {
            node* currNode = adjacentNodes.at(i);
            int weightBetween = g.weightBetween(*extractedNode, *currNode);

            if (contains(pq, currNode) && weightBetween < currNode->weight)
            {
                // Keep track of how we got to this node
                currNode->parent = extractedNode;
                finalNodes.at(currNode->nodeID) = currNode;

                // Decrease this node's key to new weight
                decreaseKey(currNode->nodeID, g.weightBetween(*extractedNode, *currNode));
            }
        }
    }

    /*
     * So basically have a meta array that actually holds the nodes, and have the 
     * priority queue only hold references to those that it can change.
     *
     * Print out the meta queue at the end
     */
    // Print out the parent value of each vertex
    for (int i = 0; i < numVerts; i++)
    {
        cout << finalNodes.at(i)->parent << endl;
    }

    return 0;
}

#endif
