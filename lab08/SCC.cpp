#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

// Strongly connected components are represented by
// appointing a root vertex for each component, where
// each vertex is assigned a root vertex of it's
// component
struct vertex {
    bool visited = false;
    int vertID;
    vector<vertex*> *neighbors = new vector<vertex*>;
    vertex *rootVertex = NULL;
};

struct edge {
    vertex *vertexOne;
    vertex *vertexTwo;
};

vector<vertex*>* processedVertexList = new vector<vertex*>;

void assign(vertex *vertOne, vertex *rootToAssign)
{
    // Only assign if a root vertex has not
    // already been assigned to vertexOne
    if (!vertOne->rootVertex)
    {
        // Assign u as belonging to the component
        // whose root is "rootToAssign"
        vertOne->rootVertex = rootToAssign;
    }
}

void visit(vertex *vert)
{
    // Don't do anything if it's already been
    // visited
    if (vert->visited)
        return;

    // Mark the vertex as visited
    vert->visited = true;

    // Visit each of these nodes' neighbors
    for (ulong i = 0; i < vert->neighbors->size(); i++)
        visit(vert->neighbors->at(i));

    // Add u to processedList
    processedVertexList->push_back(vert);
}

void scc(vector<vertex*> *vertexList, vector<edge*> *edgeList)
{

    // Get neighbors of each vert using edge list
    for (ulong i = 0; i < edgeList->size(); i++)
    {
        edge *ed = edgeList->at(i);
        
        // Grab both vertexes referenced by each
        // edge and add them to eachother's 
        // neighbor lists
        ed->vertexOne->neighbors->push_back(ed->vertexTwo);
        ed->vertexTwo->neighbors->push_back(ed->vertexOne);
    }
    
    // "Visit" each vertex
    for (ulong i = 0; i < vertexList->size(); i++)
        visit(vertexList->at(i));

    // Assign (u, root) for each vert
}

int main(int argc, char **argv)
{  
    // Get the number of verticies and edges in the
    // input
    int numVerts, numEdges;
    cin >> numVerts;
    cin >> numEdges;

    // Create initial vector of verticies
    vector<vertex*>* vertexList = new vector<vertex*>;
    
    for (int i = 0; i < numVerts; i++)
    {
        vertex *vert = new vertex;
        vert->vertID = i;
        vertexList->push_back(vert);
    }

    // Create vector of edges
    vector<edge*>* edgeList = new vector<edge*>;

    for (int i = 0; i < numEdges; i++)
    {

        int vertOneID, vertTwoID;
        edge *ed = new edge;
        cin >> vertOneID;
        cin >> vertTwoID;
        ed->vertexOne = vertexList->at(vertOneID);
        ed->vertexTwo = vertexList->at(vertTwoID);
        edgeList->push_back(ed);
    }

    scc(vertexList, edgeList);

    return 0;
}

