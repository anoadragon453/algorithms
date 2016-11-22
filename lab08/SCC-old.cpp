// SCC - find strongly connected components of a directed graph
//
// TODO: Figure out why scc's are being printed out largest vertex
// of each scc first, instead of smallest

#include <iostream>
#include <stdio.h>
#include <vector>
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

// Assign
// Assign's the rootVertex of each vertex of each SCC recursively
void assign(vertex *vertOne, vertex *rootToAssign)
{
    // Only assign if a root vertex has not
    // already been assigned to vertexOne
    if (!vertOne->rootVertex)
    {
        // Assign u as belonging to the component
        // whose root is "rootToAssign"
        vertOne->rootVertex = rootToAssign;

        // For each of vert's neighbor, 
        // do assign(neigh, rootToAssign)
        for (ulong i = 0; i < vertOne->neighbors->size(); i++)
        {
            assign(vertOne->neighbors->at(i), rootToAssign);
        }
    }
}

// Sort based on count sort
vector<vertex*> *countsort (vector<vertex*> *vec, int maxnum)
{
    // Initialize histogram and holding arrays
    vector<vertex*> *B = new vector<vertex*> (vec->size(), NULL);
    int C[maxnum];

    // Initialize histogram with 0's
    for (int i = 0; i <= maxnum; i++)
    {
        C[i] = 0;
    }

    // Count numbers in the array
    for (ulong i = 0; i < vec->size(); i++)
    {
        C[vec->at(i)->vertID]++;
    }

    // C[i] contains number of elements equal to i
    // Take sum of i,i-1
    for (int i = 1; i <= maxnum; i++)
    {
        C[i] = C[i] + C[i-1];
    }

    // Place each element of A into correct sorted pos in B
    for (int i = vec->size() - 1; i >= 0; i--)
    {
        int index = C[vec->at(i)->vertID] - 1;
        B->at(index) = vec->at(i);
        C[vec->at(i)->vertID] = index;
    }

    return B;
}

// Visit
// "Visit's" a vertex and it's neighbor's recursively
// Appending each seen vertex to processedVertexList
void visit(vertex *vert)
{
    // If the given vertex hasn't been visited...
    if (!vert->visited)
    {
        // Mark the vertex as visited
        vert->visited = true;

        // Visit each of these vertex's neighbors
        for (ulong i = 0; i < vert->neighbors->size(); i++)
            visit(vert->neighbors->at(i));

        // Add u to processedList
        processedVertexList->push_back(vert);
    }
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

    // Sort processed list
    processedVertexList = countsort(processedVertexList, vertexList->size());

    // DEBUG: Check processed list
    for (ulong i = 0; i < processedVertexList->size(); i++)
        cout << "LIST: " << processedVertexList->at(i)->vertID << endl;

    // Assign (u, u) for each processed vert
    for (ulong i = 0; i < processedVertexList->size(); i++)
        assign(processedVertexList->at(i), processedVertexList->at(i));
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

    // Figure out SCC's
    scc(vertexList, edgeList);

    // Print out SCC's
    for (ulong i = 0; i < processedVertexList->size(); i++)
    {
        cout << processedVertexList->at(i)->rootVertex->vertID << endl;
    }

    return 0;
}

