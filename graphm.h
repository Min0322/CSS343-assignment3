// -----------------------------graphm.h------------------------------
// Minseong Na
// 02/04/2023
// -------------------------------------------------------------------
// This implements Dijkstra's shortest path algorithm, 
// including recovering the paths. 
// You will find the lowest cost paths and display the cost and path 
// from every node to every other node.
// Another display routine will output one path in detail.
// -------------------------------------------------------------------
// Specifications and Assumptions:
// - It is assumed that the user will give a.txt file with the integer 
// n on the first line to indicate the number of nodes.
// - A description of each node on the next n lines.
// - Input sources node, space, destination, space, 
// and final cost on the following line
// - For the initial integer, end input with 0. 
// -------------------------------------------------------------------

#ifndef graphm_h
#define graphm_h
#include "nodedata.h"
#include "stdio.h"

class GraphM
{
    static const int MAXNODES = 101; // At most 100 nodes

    public:

        // Constructor and Destructor
        GraphM();
        ~GraphM();

        // Functions
        void buildGraph(ifstream&); // Input all data
        void findShortestPath(); // Finding the shortest path using Dijkstra's algorithm
        void insertEdge(const int, const int, const int); // Insert cost
        void removeEdge(int, int); // Remove cost
        void display(const int, const int) const; // Display a specific path
        void displayAll() const; // Display all data

    private:

        struct TableType
        {
            bool visited; // Whether node has been visited
            int dist;     // Shortest distance
            int path;     // Previous node in path of minimum distance
        };

        NodeData data[MAXNODES];          // Data for graph nodes information
        int C[MAXNODES] [MAXNODES];       // Cost array, the adjacency matrix
        int size;                         // Number of nodes in the graph
        TableType T[MAXNODES] [MAXNODES]; // Stores Dijkstra information
        void makeEmpty();                 // make the table empty
        void displayPath(int, int) const; // print path from/to node
        void displayName(int, int) const; // print descriptions
};

#endif;
