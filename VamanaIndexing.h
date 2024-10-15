#ifndef VAMANAINDEXING_H
#define VAMANAINDEXING_H

#include <iostream>
#include <vector>
#include <random>

using namespace std;

/*main idea: the final graph will be a N sized table which contains a pointer to a vector (to describe the node name)
and an R sized table of pointers to other vectors (to describe the neighbors of the node). 

Each node of the graph will look like this:
_____________________
|   vec*            |
|                   |
| neighbors of vec  |
|  _______________  |
|  | v1*| v2*| v3*| |
|  |____|____|____| |
|___________________|

The Graph: In the end we have the N sized table containing "nodes" like above.
*/


// Create the node's structure of the graph
struct GraphNode {
    vector<float>* node_name;          // The node name (e.g. vector 1)
    vector<float>** neighbors;         // Array of neighbors (array of pointers to vectors)
};


// Creates a random R-regular directed graph
GraphNode* CreateGraph(const vector<vector<float>>& data, int size, int R);

// Vamana Indexing Algorithm
void VamanaIndexing(const vector<vector<float>>& data, int size, int R);

#endif