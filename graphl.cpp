// -----------------------------graphl.cpp-----------------------------
// Minseong Na
// 02/04/2023
// --------------------------------------------------------------------
// this project is to display the graph information and implement depth-first.
// Description of each node is 50 chars max length. 
// There can be several graphs, each has at most 100 nodes.
// edges in the input are always shown in reverse order in the output
// --------------------------------------------------------------------
// Specifications and Assumptions:
// - the output should be in reverse order in which they are in file.
// - input should be correctly formatted and valid.
// --------------------------------------------------------------------


#include "graphl.h"


// --------------------------------------------------------------------
// Default constructor
// Make an empty table and initializes all values
// --------------------------------------------------------------------
GraphL :: GraphL()
{
    size = 0;

    for(int i = 0; i < MAXNODES; i++)
    {
        graph[i].visited = false;
        graph[i].edgeHead = NULL;
        graph[i].data = NULL;
    }
}

// --------------------------------------------------------------------
// Destructor
// Eliminates the memory in a table
// --------------------------------------------------------------------
GraphL :: ~GraphL()
{
    makeEmpty();
}

// --------------------------------------------------------------------
// BuildGraph
// Builds up graph node information and adjacency matrix of edges
// between each node reading from a file
// --------------------------------------------------------------------
void GraphL :: buildGraph(ifstream& infile2)
{

    int from, to;

    infile2 >> size;

    if(size > 0) 
    {
        string str;
        getline(infile2, str);
        for(int i = 1; i <= size; i++) 
        {

            graph[i].data = new NodeData();
            graph[i].data -> setData(infile2);

        }

        while(infile2 >> from >> to) 
        {
            if(from == 0) 
            {
                break;
            }

            EdgeNode* node = new EdgeNode;
            node -> adjGraphNode = to;

            if(graph[from].edgeHead == NULL) 
            {

                graph[from].edgeHead = node;
                graph[from].edgeHead -> nextEdge = NULL;

            } else 
            {

                node -> nextEdge = graph[from].edgeHead;
                graph[from].edgeHead = node;

            }
        }
    }
}

// ----------------------------------------------------------------------
// depthFirstSearch
// makes a depth-first search and displays each node in depth-first order
// ----------------------------------------------------------------------
void GraphL :: depthFirstSearch()
{
    cout << "Depth-first ordering: ";

    for(int i = 1; i <= size; i++) 
    { 

        if(!graph[i].visited) // Checking whether the node has been visited
        {         
            dfsHelper(i);     // Call helper
        }

    }

    cout << "\n" << endl;
}

// --------------------------------------------------------------------
// displayGraph
// Displays the information of the nodes and edge in the graph
// --------------------------------------------------------------------
void GraphL :: displayGraph()
{
    cout << "Graph: " << endl;

    for(int i = 1; i <= size; i++) 
    {

        cout << "Node" << i << "\t\t " << *graph[i].data << endl << endl;

        EdgeNode* current = graph[i].edgeHead; // Assign to the current one
        while(current != NULL)                 // Check for linked list
        {   

            cout << setw(7) << "edge  " << i << setw(2) << current -> adjGraphNode << endl;
            current = current -> nextEdge;     // Move pointer to next node

        }
    }
    
    cout << endl;
}

// --------------------------------------------------------------------
// makeEmpty
// make the table empty
// --------------------------------------------------------------------
void GraphL :: makeEmpty()
{
        for(int i = 1; i <= size; i++) 
        {

        graph[i].visited = false;
        delete graph[i].data;           // Deleting edge name
        graph[i].data = NULL;           // Reset edge name

        if(graph[i].edgeHead != NULL) 
        {

            EdgeNode* target = graph[i].edgeHead;
            while(target != NULL) 
            {

                graph[i].edgeHead = graph[i].edgeHead -> nextEdge;
                delete target;
                target = NULL;
                target = graph[i].edgeHead;

            }
        }
    }
}

// --------------------------------------------------------------------
// dfsHelper
// Helper function of depthFirstSearch()
// Find the depthFirstSearch by Recursive method
// --------------------------------------------------------------------

void GraphL::dfsHelper(int v)
{
    cout << setw(2) << v;   // print node
    graph[v].visited = true;   // mark visited
    EdgeNode* current = graph[v].edgeHead; // move pointer to head

    while (current != NULL) // loop till end of linked list
    {
        if (!graph[current -> adjGraphNode].visited) // check if visited
        {
            dfsHelper(current -> adjGraphNode);  // call helper
        }

        current = current -> nextEdge;    // move pointer to next node in linked list
    }
}