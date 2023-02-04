// -----------------------------graphm.cpp------------------------------
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


#include "graphm.h"

using namespace std;

// --------------------------------------------------------------------
// Default constructor
// Make an empty table and initializes all values
// --------------------------------------------------------------------

GraphM :: GraphM()
{
    size = 0;
    for(int i = 0; i < MAXNODES; i++)
    {
        for(int j = 0; j < MAXNODES; j++)
        {
                C[i][j] = INT_MAX;
                T[i][j].visited = false;
                T[i][j].dist = INT_MAX;
                T[i][j].path = 0;
        }
    }
}

// --------------------------------------------------------------------
// Destructor
// Eliminates the memory in a table
// --------------------------------------------------------------------

GraphM :: ~GraphM()
{
    makeEmpty();
}

// --------------------------------------------------------------------
// BuildGraph
// Builds up graph node information and adjacency matrix of edges
// between each node reading from a file
// --------------------------------------------------------------------

void GraphM :: buildGraph(ifstream& infile1)
{

    makeEmpty();
    int from, to, dist;
    infile1 >> size;

    if(size > 0) 
    {

        string str;
        getline(infile1, str);

        for(int i = 1; i <= size; i++) 
        {
            data[i].setData(infile1);
        }
        while(infile1 >> from >> to >> dist) 
        {
            if(from == 0) 
            {
                break;
            }
            insertEdge(from, to, dist);
        }
    }
}


// --------------------------------------------------------------------
// findShortestPath
// Find the shortest path between every node to other nodes
// Using Dijkstra's algorithm
// --------------------------------------------------------------------
void GraphM :: findShortestPath()
{
    for(int source = 1; source <= size; source++) 
    {

        T[source][source].dist = 0;
        for(int i = 1; i <=size; i++) 
        {

            int v = -1;
            int minDist = INT_MAX;
            for(int j = 1; j <= size; j++) 
            {

                if(T[source][j].dist <minDist && !T[source][j].visited) 
                {
                    minDist = T[source][j].dist;
                    v = j;
                }
            }

            if(v == -1) 
            {
                break;
            }

            T[source][v].visited = true;

            for(int w = 1; w <= size; w++) 
            {

                if(C[v][w] < INT_MAX && !T[source][w].visited) 
                {

                    if(T[source][v].dist + C[v][w] < T[source][w].dist) 
                    {

                        T[source][w].dist = T[source][v].dist + C[v][w];
                        T[source][w].path = v;
                    }
                }
            }
        }
    }
    for(int i = 1; i <= size; i++) 
    {
        for(int j = 1; j <= size; j++) 
        {
            T[i][j].visited = false;
        }
    }
}

// --------------------------------------------------------------------
// insertEdge
// Inserting an edge into a graph between two nodes
// --------------------------------------------------------------------
void GraphM :: insertEdge(const int from, const int to, const int dist)
{
    C[from][to] = dist;   // edge inserted
    findShortestPath();   // redo Dijkstra's algorithm with change
}

// --------------------------------------------------------------------
// removeEdge
// Removing an edge between two nodes
// --------------------------------------------------------------------
void GraphM :: removeEdge(int from, int to)
{
    C[from][to] = INT_MAX;  // edge removed
    findShortestPath();     // redo Dijkstra's algorithm with change
}


// --------------------------------------------------------------------
// display
// Displays the shortest distance with path info 
// between the fromNode to toNode
// Using two helper functions: displayPath, displayName
// --------------------------------------------------------------------
void GraphM :: display(int from, int to) const
{
    if ((from > size || from < 0) || (to > size || to < 0)) 
    {
        cout << setw(7) << from << setw(7) << to;   
        cout << setw(15) << "----" << endl; 

        return; 
    }

    cout << setw(7) << from << setw(7) << to;   

    if (T[from][to].dist != INT_MAX)    
    {
        cout << setw(12) << T[from][to].dist << setw(15); 

        displayPath(from, to); 
        cout << endl;

        displayName(from, to); 
    }
    else    // no adjacent node
    {
        cout << setw(15) << "----" << endl;
    }

    cout << endl;
}

// --------------------------------------------------------------------
// displayAll
// Displays all the shortest distance of all algorithms
// Using helper function: displayPath
// --------------------------------------------------------------------
void GraphM :: displayAll() const
{
    // Title
    cout << "Description" << setw(20) << "From node" << setw(10) << "To node"
    << setw(14) << "Dijkstra's" << setw(7) << "Path" << endl;

    for (int from = 1; from <= size; from++)
    {

        cout << data[from] << endl << endl;     
        for (int to = 1; to <= size; to++)
        {
            if (T[from][to].dist != 0)
            {

                cout << setw(27) << from;   
                cout << setw(10) << to;     

                if (T[from][to].dist == INT_MAX)
                {
                    cout << setw(12) << "----" << endl; 
                }
                else
                {

                    cout << setw(12) << T[from][to].dist;   
                    cout << setw(10);

                    displayPath(from, to); // call helper
                    cout << endl;
                }
            }
        }
    }
}


// --------------------------------------------------------------------
// makeEmpty
// make the table empty
// --------------------------------------------------------------------
void GraphM :: makeEmpty()
{
    size = 0;

    for(int i = 0; i < MAXNODES; i++) 
    {

        for(int j = 0; j < MAXNODES; j++) 
        {

            T[i][j].dist = INT_MAX;
            T[i][j].visited = false;
            T[i][j].path = 0;
            C[i][j] = INT_MAX;

        }
    }
}

// --------------------------------------------------------------------
// displayPath
// outputs Dijkstra's path as integer values to cout and 
// retrieves the path backwards using recursion and prints in proper order
// --------------------------------------------------------------------
void GraphM :: displayPath(int from, int to) const
{

    int v = T[from][to].path;

    if(v != 0) 
    {
         
        displayPath(from, v);
        cout << to << " ";

    } else if (from == to) 
    {
        cout << to << " ";
    }
}

// --------------------------------------------------------------------
// displayName
// displays the path data of the two integers that passed in
// --------------------------------------------------------------------
void GraphM :: displayName(int from, int to) const
{

    int v = T[from][to].path;
    
    if(v != 0) 
    {
        displayName(from, v);
        cout << data[to] << endl;
    } else if (from == to) 
    {
        cout << data[to] << endl;
    }
    cout << endl;
}

