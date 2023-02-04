// -----------------------------graphl.h-----------------------------
// Minseong Na
// 02/04/2023
// ------------------------------------------------------------------
// this project is to display the graph information and implement depth-first.
// Description of each node is 50 chars max length. 
// There can be several graphs, each has at most 100 nodes.
// edges in the input are always shown in reverse order in the output
// ------------------------------------------------------------------
// Specifications and Assumptions:
// - the output should be in reverse order in which they are in file.
// - input should be correctly formatted and valid.
// ------------------------------------------------------------------

#ifndef GRAPHL_H
#define	GRAPHL_H
#include <cstdlib>
#include <iomanip>
#include "nodedata.h"

class GraphL 
{
    static const int MAXNODES = 101; // maximum limit of nodes

    public:

        // Constructor and Destructor
        GraphL();
        ~GraphL();

        // Functions
        void buildGraph(ifstream&); // Input all data
        void displayGraph();        // Display all data
        void depthFirstSearch();    // Use depth-first search algorithm

    private:

        int size;                   // Number of nodes in the graph
        struct EdgeNode;            // Struct declaration
        struct GraphNode           // Struct for simplicity           
        {
            EdgeNode* edgeHead;     // Head of the list of edges
            NodeData* data;         // Info on the graph node
            bool visited;           // Whether node has been visited
        };
        struct EdgeNode             // Struct for linked list
        {
            int adjGraphNode;       // Subscript of the adjacent graph node
            EdgeNode* nextEdge;     // Next node
        };

        GraphNode graph[MAXNODES];  // Graph node size

        // Helper Functions
        void makeEmpty();           // Make the table empty
        void dfsHelper(int);        // Helper for depthFirstSearch()
        void insertEdge(const int, const int); // Inserting edge
};

#endif