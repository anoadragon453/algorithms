#include "graph.h"
#include <iostream>
#include <list>
#include <stack>
#include <vector>
using namespace std;

Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];

    // Initialize the print vector with V 0's
    // (to be replaced later)
    this->printVector = new vector<int> (V, 0);
}

// A recursive function to print DFS starting from v
void Graph::DFSUtil(int v, bool visited[], vector<int> &numVector)
{
    // Mark the current node as visited and print it
    visited[v] = true;

    // If nothing in there, just push
    if (numVector.empty())
    {
        numVector.push_back(v);
    } else {
        // Run through nutil we find number that's bigger than 
        // or equal to us, then push before it
        bool gotem = false;
        for (int i = 0; i < numVector.size(); i++)
        {
            if (v <= numVector.at(i))
            {
                gotem = true;
                numVector.insert(numVector.begin() + i, v);
                i++;
            }
        }
        if (!gotem)
            numVector.push_back(v);
    }
 
    // Recur for all the vertices adjacent to this vertex
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visited[*i])
            DFSUtil(*i, visited, numVector);
}
 
Graph Graph::getTranspose()
{
    Graph g(V);
    for (int v = 0; v < V; v++)
    {
        // Recur for all the vertices adjacent to this vertex
        list<int>::iterator i;
        for(i = adj[v].begin(); i != adj[v].end(); ++i)
        {
            g.adj[*i].push_back(v);
        }
    }
    return g;
}
 
void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w); // Add w to v’s list.
}
 
void Graph::fillOrder(int v, bool visited[], stack<int> &Stack)
{
    // Mark the current node as visited and print it
    visited[v] = true;
 
    // Recur for all the vertices adjacent to this vertex
    list<int>::iterator i;
    for(i = adj[v].begin(); i != adj[v].end(); ++i)
        if(!visited[*i])
            fillOrder(*i, visited, Stack);
 
    // All vertices reachable from v are processed by now, push v 
    Stack.push(v);
}
 
// The main function that finds and prints all strongly connected 
// components
void Graph::printSCCs()
{
    stack<int> Stack;
 
    // Mark all the vertices as not visited (For first DFS)
    bool *visited = new bool[V];
    for(int i = 0; i < V; i++)
        visited[i] = false;
 
    // Fill vertices in stack according to their finishing times
    for(int i = 0; i < V; i++)
        if(visited[i] == false)
            fillOrder(i, visited, Stack);
 
    // Create a reversed graph
    Graph g = getTranspose();
 
    // Mark all the vertices as not visited (For second DFS)
    for(int i = 0; i < V; i++)
        visited[i] = false;
 
    // Now process all vertices in order defined by Stack
    while (Stack.empty() == false)
    {
        // Pop a vertex from stack
        int v = Stack.top();
        Stack.pop();

        vector<int> *numVector = new vector<int>; // Holds numbers for sorting before printing
         
 
        // Print Strongly connected component of the popped vertex
        if (visited[v] == false)
        {
            g.DFSUtil(v, visited, *numVector);

            // Grab ints from numVector and insert into printVector
            int minimum = numVector->at(0);
            for (int i = 0; i < numVector->size(); i++)
            {
                printVector->at(numVector->at(i)) = minimum;
            }

            // Clear numVector to make room for next SCC
            numVector->clear();
        }
    }

    // Print out contents of printVector
    for (int i = 0; i < printVector->size(); i++)
    {
        cout << printVector->at(i) << endl;
    }

}
